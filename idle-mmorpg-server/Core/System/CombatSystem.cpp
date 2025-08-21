#include "CombatSystem.h"

#include <algorithm>
#include <cmath>
#include <iostream>

#include <Commons/DecimalHelper.h>

#include "LootSystem.h"
#include "QuestSystem.h"

namespace Core::System {

CombatSystem::CombatSystem( Model::Location* location ) :
    _location( location ),
    _progressionSystem() {}

void CombatSystem::computeCombatActionDuration( Model::Character* character ) {
    double speed = character->combatAttributes().speed();

    int minTicks = 5;
    int maxTicks = 40;

    double adjustedSpeed = speed > 0 ? speed : 1.0;
    double maxSpeed = 100.0;

    if ( adjustedSpeed > maxSpeed ) {
        adjustedSpeed = maxSpeed;
    }

    double normalized = std::sqrt( adjustedSpeed / maxSpeed );

    int duration = static_cast<int>( maxTicks - normalized * ( maxTicks - minTicks ) );

    duration = std::clamp( duration, minTicks, maxTicks );

    character->combatAction().setCounter( 0 );
    character->combatAction().setDuration( duration );
}

void CombatSystem::computeCombatActionDuration( Model::Creature* creature ) {
    double speed = creature->speed();

    int minTicks = 5;
    int maxTicks = 40;

    double adjustedSpeed = speed > 0 ? speed : 1.0;
    double maxSpeed = 100.0;

    if ( adjustedSpeed > maxSpeed ) {
        adjustedSpeed = maxSpeed;
    }

    double normalized = std::sqrt( adjustedSpeed / maxSpeed );

    int duration = static_cast<int>( maxTicks - normalized * ( maxTicks - minTicks ) );

    duration = std::clamp( duration, minTicks, maxTicks );

    creature->combatAction().setCounter( 0 );
    creature->combatAction().setDuration( duration );
}

void CombatSystem::computeHitDamage( const std::string& sessionId, Model::Character* character, Model::Creature* creature ) {
    std::cout << "CombatSystem::computeHitDamage [CHARACTER] " << character->name() << " [CREATURE] " << creature->name() << std::endl;

    double newStamina = character->vitals().stamina() - 1;
    newStamina = std::max( 0.0, newStamina );
    character->vitals().setStamina( newStamina );

    auto skills = CombatSystem::combatSkill( character );

    if ( skills.empty() ) {
        skills.push_back( "unarmed" );
    }

    double chanceDiff = character->combatAttributes().accuracy() + character->attributes().dexterity() - creature->evasion();
    double hitChance = 0.5 + ( 0.005 * chanceDiff );
    hitChance = std::clamp( hitChance, 0.05, 0.95 );

    if ( !rollChance( hitChance ) ) {
        std::cout << "Attack missed!" << std::endl;
        return;
    }
    _progressionSystem.applyExperience( sessionId, character, "agility", creature->evasion() );

    double minDamage = ( character->combatAttributes().attack() + character->attributes().strength() ) / 2;
    double maxDamage = character->combatAttributes().attack() + character->attributes().strength();
    double damage = rollRange( minDamage, maxDamage ) - creature->defense();
    damage = std::max( 1.0, damage );

    int masteryLevel = 0;
    for ( const auto& skill : skills ) {
        masteryLevel = std::max( masteryLevel, character->skills().skillLevel( skill ) );
    }
    double critChance = character->combatAttributes().criticalChance();
    critChance += masteryLevel * 0.005;

    if ( rollChance( critChance ) ) {
        damage *= character->combatAttributes().criticalMultiplier();
        std::cout << "Critical hit!" << std::endl;
    }

    double newHealth = creature->vitals().health() - damage;
    newHealth = std::max( 0.0, newHealth );
    creature->vitals().setHealth( newHealth );

    double xpShare = damage / std::max( 1, static_cast<int>( skills.size() ) );
    for ( const auto& skill : skills ) {
        _progressionSystem.applyExperience( sessionId, character, skill, xpShare );
    }

    std::cout << "Hit for " << damage << " damage. Creature HP left: " << creature->vitals().health() << std::endl;
}

void CombatSystem::computeHitDamage( Model::Creature* creature, const std::string& sessionId, Model::Character* character ) {
    std::cout << "CombatSystem::computeHitDamage [CREATURE] " << creature->name() << " [CHARACTER] " << character->name() << std::endl;

    double newStamina = creature->vitals().stamina() - 1;
    newStamina = std::max( 0.0, newStamina );
    creature->vitals().setStamina( newStamina );

    bool hasShieldEquipped = ( character->equipment().leftHand().item() && character->equipment().leftHand().item()->category() == "shield" ) ||
                             ( character->equipment().rightHand().item() && character->equipment().rightHand().item()->category() == "shield" );

    int minCreatureAttack = static_cast<int>( creature->minAttack() );
    int maxCreatureAttack = static_cast<int>( creature->maxAttack() );
    double damage = rollRange( minCreatureAttack, maxCreatureAttack );

    if ( hasShieldEquipped ) {
        int blockingLevel = character->skills().skillLevel( "blocking" );
        double blockChance = 0.5 + ( 0.005 * ( blockingLevel - creature->accuracy() ) );
        blockChance = std::clamp( blockChance, 0.05, 0.95 );

        if ( rollChance( blockChance ) ) {
            std::cout << "Attack blocked by shield!" << std::endl;
            _progressionSystem.applyExperience( sessionId, character, "blocking", creature->accuracy() );

            int shieldLevel = character->skills().skillLevel( "shield_mastery" );
            double reduction = 0.5 + ( 0.005 * shieldLevel );
            reduction = std::clamp( reduction, 0.05, 1.0 );
            damage *= ( 1.0 - reduction );
            _progressionSystem.applyExperience( sessionId, character, "shield_mastery", damage );
        }

    } else {
        int evasionLevel = character->skills().skillLevel( "evasion" );
        double evasionChance = ( 0.5 + 0.005 * ( evasionLevel - creature->accuracy() ) );
        evasionChance = std::clamp( evasionChance, 0.05, 0.95 );

        if ( rollChance( evasionChance ) ) {
            std::cout << "Attack missed due to evasion!" << std::endl;
            _progressionSystem.applyExperience( sessionId, character, "evasion", creature->accuracy() );
            return;
        }
    }

    double newHealth = character->vitals().health() - damage;
    newHealth = std::max( 0.0, newHealth );
    character->vitals().setHealth( newHealth );

    int xpEndurance = std::max( 1, static_cast<int>( damage * 0.5 ) );
    _progressionSystem.applyExperience( sessionId, character, "endurance", xpEndurance );

    std::cout << "Hit for " << damage << " damage. Character HP left: " << character->vitals().health() << std::endl;
}

void CombatSystem::computeLoot( std::unordered_map<std::string, Model::Character*> characters, std::vector<Model::Creature*> creatures ) {
    if ( characters.empty() ) {
        return;
    }

    for ( const auto& creature : creatures ) {
        for ( const auto& lootEntry : creature->loot() ) {

            double roll = static_cast<double>( rand() ) / RAND_MAX;
            if ( roll <= lootEntry.chance() ) {
                auto it = characters.begin();
                std::advance( it, rand() % characters.size() );
                Model::Character* receiver = it->second;

                int amount = lootEntry.minAmount() + ( rand() % ( lootEntry.maxAmount() - lootEntry.minAmount() + 1 ) );
                std::cout << "[CHARACTER] " << receiver->name() << " [QUANTITY] " << amount << " [ITEM] " << lootEntry.id() << std::endl;
                LootSystem::addItem( it->first, receiver, lootEntry.id(), amount );
            }
        }
    }
}

void CombatSystem::computeExperience( std::unordered_map<std::string, Model::Character*> characters, std::vector<Model::Creature*> creatures ) {
    double totalXP = 0.0;
    for ( const auto& creature : creatures ) {
        totalXP += creature->experience();
    }

    if ( characters.empty() || totalXP <= 0 ) {
        return;
    }

    double xpPerCharacter = totalXP / characters.size();
    for ( auto& [ sessionId, character ] : characters ) {
        if ( character->vitals().health() > 0 ) {

            for ( const auto& creature : creatures ) {
                Core::System::QuestSystem::updateKillQuest( sessionId, character, creature->id() );
            }

            _progressionSystem.applyExperience( sessionId, character, xpPerCharacter );
            std::cout << "[CHARACTER] " << character->name() << " [XP] " << xpPerCharacter << " XP.\n";
        }
    }
}

bool CombatSystem::rollChance( double probability ) {
    probability = std::clamp( probability, 0.0, 1.0 );
    double roll = static_cast<double>( rand() ) / RAND_MAX;
    return roll < probability;
}

double CombatSystem::rollRange( double min, double max ) {
    double roll = static_cast<double>( rand() ) / RAND_MAX;
    return min + roll * ( max - min );
}

std::vector<std::string> CombatSystem::combatSkill( Model::Character* character ) {
    const Model::Item* leftHand = character->equipment().leftHand().item();
    const Model::Item* rightHand = character->equipment().rightHand().item();

    std::vector<std::string> skills = {};

    if ( !leftHand && !rightHand ) {
        return { "unarmed" };
    }

    std::string leftSkill = combatSkillByWeapon( leftHand );
    std::string rightSkill = combatSkillByWeapon( rightHand );

    if ( !leftSkill.empty() ) {
        skills.push_back( leftSkill );
    }

    if ( !rightSkill.empty() && rightSkill != leftSkill ) {
        skills.push_back( rightSkill );
    }

    // TODO Add dual-wielding

    return skills;
}

std::string CombatSystem::combatSkillByWeapon( const Model::Item* weapon ) {
    if ( !weapon ) {
        return "";
    }

    const std::string& category = weapon->category();
    if ( category == "sword" ) {
        return "sword_mastery";
    }

    if ( category == "axe" ) {
        return "axe_mastery";
    }

    if ( category == "dagger" ) {
        return "dagger_mastery";
    }

    return "";
}

} // namespace Core::System
