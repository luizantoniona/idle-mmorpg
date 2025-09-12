#include "CombatSystem.h"

#include <algorithm>
#include <cmath>
#include <iostream>

#include <Commons/DecimalHelper.h>
#include <Commons/Singleton.h>
#include <Core/Manager/ServerConfigurationManager.h>

#include "LootSystem.h"
#include "NotificationSystem.h"
#include "QuestSystem.h"

namespace Core::System {

CombatSystem::CombatSystem( Model::Location* location ) :
    _tickRate( Commons::Singleton<Core::Manager::ServerConfigurationManager>::instance().tickRate() ),
    _location( location ),
    _progressionSystem() {}

void CombatSystem::computeCombatActionDuration( Model::Character* character ) {
    double attackSpeed = character->combatAttributes().attackSpeed();

    int duration = _tickRate / attackSpeed;

    character->combatAction().setCounter( 0 );
    character->combatAction().setDuration( duration );
}

void CombatSystem::computeCombatActionDuration( Model::Creature* creature ) {
    double attackSpeed = creature->attackSpeed();

    int duration = _tickRate / attackSpeed;

    creature->combatAction().setCounter( 0 );
    creature->combatAction().setDuration( duration );
}

void CombatSystem::computeHitDamage( const std::string& sessionId, Model::Character* character, Model::Creature* creature ) {
    double newStamina = character->vitals().stamina() - 1;
    newStamina = std::max( 0.0, newStamina );
    character->vitals().setStamina( newStamina );

    NotificationSystem::notifyCharacterVitals( sessionId, character );

    auto skills = CombatSystem::combatSkill( character );

    int masteryLevel = 0;
    for ( const auto& skill : skills ) {
        masteryLevel = std::max( masteryLevel, character->skills().skillLevel( skill ) );
    }

    double chanceDiff = masteryLevel + character->attributes().dexterity() - creature->evasion();
    double hitChance = 0.5 + ( 0.005 * chanceDiff );
    hitChance = std::clamp( hitChance, 0.05, 0.95 );

    if ( !rollChance( hitChance ) ) {
        return;
    }

    double minDamage = ( character->combatAttributes().attack() + character->attributes().strength() ) / 2;
    double maxDamage = character->combatAttributes().attack() + character->attributes().strength();
    double damage = rollRange( minDamage, maxDamage ) - creature->defense();
    damage = std::max( 1.0, damage );

    double newHealth = creature->vitals().health() - damage;
    newHealth = std::max( 0.0, newHealth );
    creature->vitals().setHealth( newHealth );

    double xpShare = damage / std::max( 1, static_cast<int>( skills.size() ) );
    for ( const auto& skill : skills ) {
        _progressionSystem.applyExperience( sessionId, character, skill, xpShare );
    }

    std::cout << "CombatSystem::computeHitDamage"
              << " [CHARACTER] " << character->name()
              << " [DAMAGE] " << damage
              << " [CREATURE] " << creature->name()
              << " [HP LEFT]: " << creature->vitals().health() << std::endl;
}

void CombatSystem::computeHitDamage( Model::Creature* creature, const std::string& sessionId, Model::Character* character ) {
    std::cout << "CombatSystem::computeHitDamage [CREATURE] " << creature->name() << " [CHARACTER] " << character->name() << std::endl;

    double newStamina = creature->vitals().stamina() - 1;
    newStamina = std::max( 0.0, newStamina );
    creature->vitals().setStamina( newStamina );

    bool hasShieldEquipped = ( character->equipment().leftHand().item() && character->equipment().leftHand().item()->category() == "shield" ) ||
                             ( character->equipment().rightHand().item() && character->equipment().rightHand().item()->category() == "shield" );

    double maxCreatureAttack = creature->attack();
    double damage = rollRange( 0, maxCreatureAttack );

    damage -= character->combatAttributes().defense();
    damage = std::max( 0, damage );

    if ( hasShieldEquipped ) {
        int shieldLevel = character->skills().skillLevel( "shield_mastery" );
        double blockChance = 0.5 + ( 0.005 * ( shieldLevel - creature->accuracy() ) );
        blockChance = std::clamp( blockChance, 0.05, 0.95 );

        if ( rollChance( blockChance ) ) {
            _progressionSystem.applyExperience( sessionId, character, "shield_mastery", creature->accuracy() );

            double reduction = 0.5 + ( 0.005 * shieldLevel );
            reduction = std::clamp( reduction, 0.05, 1.0 );
            damage *= ( 1.0 - reduction );
            _progressionSystem.applyExperience( sessionId, character, "shield_mastery", damage );
        }

    } else {
        double evasionChance = ( 0.5 + 0.005 * ( character->attributes().dexterity() - creature->accuracy() ) );
        evasionChance = std::clamp( evasionChance, 0.05, 0.95 );

        if ( rollChance( evasionChance ) ) {
            return;
        }
    }

    double newHealth = character->vitals().health() - damage;
    newHealth = std::max( 0.0, newHealth );
    character->vitals().setHealth( newHealth );

    int xpResistance = std::max( 1, static_cast<int>( damage * 0.5 ) );
    _progressionSystem.applyExperience( sessionId, character, "resistance", xpResistance );

    NotificationSystem::notifyCharacterVitals( sessionId, character );

    std::cout << "CombatSystem::computeHitDamage"
              << " [CREATURE] " << creature->name()
              << " [DAMAGE] " << damage
              << " [CHARACTER] " << character->name()
              << " [HP LEFT]: " << character->vitals().health() << std::endl;
}

void CombatSystem::computeSpellDamage( const std::string& sessionId, Model::Character* character, Model::Creature* creature, Model::CharacterSpell* characterSpell ) {
    double newMana = character->vitals().mana() - characterSpell->spell()->manaCost();
    newMana = std::max( 0.0, newMana );
    character->vitals().setMana( newMana );

    characterSpell->setCount( 0 );

    int focusLevel = character->skills().skillLevel( "focus" );

    double hitChance = 0.5 + 0.005 * ( focusLevel - creature->evasion() );
    hitChance = std::clamp( hitChance, 0.05, 0.95 );
    if ( !rollChance( hitChance ) ) {
        std::cout << character->name() << " missed spell " << characterSpell->spell()->name() << " on " << creature->name() << std::endl;
        return;
    }

    double minDamage = characterSpell->spell()->effect().value();
    double maxDamage = minDamage + character->attributes().intelligence();
    double damage = rollRange( minDamage, maxDamage );

    double newHealth = creature->vitals().health() - damage;
    newHealth = std::max( 0.0, newHealth );
    creature->vitals().setHealth( newHealth );

    _progressionSystem.applyExperience( sessionId, character, "focus", damage );

    std::cout << character->name() << " casts " << characterSpell->spell()->name() << " dealing " << damage << " damage to " << creature->name() << std::endl;
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
        skills.push_back( "fist_mastery" );
        return skills;
    }

    std::string leftSkill = combatSkillByWeapon( leftHand );
    std::string rightSkill = combatSkillByWeapon( rightHand );

    if ( !leftSkill.empty() ) {
        skills.push_back( leftSkill );
    }

    if ( !rightSkill.empty() ) {
        skills.push_back( rightSkill );
    }

    if ( skills.empty() ) {
        skills.push_back( "fist_mastery" );
    }

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
