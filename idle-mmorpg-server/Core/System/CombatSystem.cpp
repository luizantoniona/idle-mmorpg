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
    _progressionSystem() {
}

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

    int masteryLevel = 0;
    for ( const auto& skill : skills ) {
        masteryLevel = std::max( masteryLevel, character->skills().skill( skill )->level() );
    }

    double diff = ( character->combatAttributes().accuracy() + character->attributes().dexterity() ) - creature->evasion();
    double hitChance = 0.5 + diff * 0.03;
    hitChance += masteryLevel * 0.005;
    hitChance = std::clamp( hitChance, 0.05, 0.95 );

    double roll = static_cast<double>( rand() ) / RAND_MAX;
    if ( roll > hitChance ) {
        std::cout << "Attack missed!" << std::endl;
        return;
    }

    double baseDamage = character->combatAttributes().attack() + character->attributes().strength();
    double damage = baseDamage - creature->defense();
    damage *= ( 1.0 + masteryLevel * 0.01 );

    double critRoll = static_cast<double>( rand() ) / RAND_MAX;
    double critChance = character->combatAttributes().criticalChance();

    critChance += masteryLevel * 0.002;

    if ( critRoll < critChance ) {
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

    int evasionLevel = character->skills().skill( "evasion" )->level();
    int resilienceLevel = character->skills().skill( "resilience" )->level();

    double diff = creature->accuracy() - ( character->combatAttributes().evasion() + character->attributes().dexterity() );
    double hitChance = 0.5 + diff * 0.03;
    hitChance -= evasionLevel * 0.005;
    hitChance = std::clamp( hitChance, 0.05, 0.95 );

    double roll = static_cast<double>( rand() ) / RAND_MAX;
    if ( roll > hitChance ) {
        std::cout << "Attack missed!" << std::endl;
        _progressionSystem.applyExperience( sessionId, character, "evasion", creature->accuracy() );
        return;
    }

    int minAtk = static_cast<int>( creature->minAttack() );
    int maxAtk = static_cast<int>( creature->maxAttack() );
    int randAtk = minAtk + ( rand() % ( maxAtk - minAtk + 1 ) );
    double damage = static_cast<double>( randAtk );

    damage *= ( 1.0 - resilienceLevel * 0.005 );
    damage = std::max( 0.0, damage );

    bool hasShieldEquipped = ( character->equipment().leftHand().item() && character->equipment().leftHand().item()->category() == "shield" ) ||
                             ( character->equipment().rightHand().item() && character->equipment().rightHand().item()->category() == "shield" );

    if ( hasShieldEquipped ) {
        int shieldLevel = character->skills().skill( "shield_mastery" )->level();
        double blockChance = 0.05 + 0.05 * shieldLevel;
        blockChance = std::clamp( blockChance, 0.05, 0.95 );

        double blockRoll = static_cast<double>( rand() ) / RAND_MAX;
        if ( blockRoll < blockChance ) {
            std::cout << "Attack blocked by shield!" << std::endl;
            int xpBlock = std::max( 1, static_cast<int>( damage * 0.5 ) );
            _progressionSystem.applyExperience( sessionId, character, "shield_mastery", damage * 0.5 );
            damage *= 0.5;
        }
    }

    double newHealth = character->vitals().health() - damage;
    newHealth = std::max( 0.0, newHealth );
    character->vitals().setHealth( newHealth );

    int xpResilience = std::max( 1, static_cast<int>( damage * 0.5 ) );
    _progressionSystem.applyExperience( sessionId, character, "resilience", xpResilience );

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

std::vector<std::string> CombatSystem::combatSkill( Model::Character* character ) {
    const Model::Item* leftHand = character->equipment().leftHand().item();
    const Model::Item* rightHand = character->equipment().rightHand().item();

    std::vector<std::string> skills = {};

    if ( !leftHand && !rightHand ) {
        return { "unarmed" };
    }

    auto getSkillForWeapon = []( const Model::Item* weapon ) -> std::string {
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

        if ( category == "club" ) {
            return "club_mastery";
        }

        if ( category == "dagger" ) {
            return "dagger_mastery";
        }

        return "";
    };

    std::string leftSkill = getSkillForWeapon( leftHand );
    std::string rightSkill = getSkillForWeapon( rightHand );

    if ( !leftSkill.empty() ) {
        skills.push_back( leftSkill );
    }

    if ( !rightSkill.empty() && rightSkill != leftSkill ) {
        skills.push_back( rightSkill );
    }

    // TODO Add dual-wielding

    return skills;
}

} // namespace Core::System
