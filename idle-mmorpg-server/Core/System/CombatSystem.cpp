#include "CombatSystem.h"

#include <algorithm>
#include <iostream>

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

    auto weaponSkill = CombatSystem::combatSkill( character );
    int weaponSkillLevel = character->skills().skillLevel( weaponSkill );

    double chanceDiff = weaponSkillLevel - creature->evasion();
    double hitChance = 0.5 + ( 0.005 * chanceDiff );
    hitChance = std::clamp( hitChance, 0.05, 0.95 );

    if ( !rollChance( hitChance ) ) {
        return;
    }

    double maxDamage = character->combatAttributes().attack() + ( weaponSkillLevel * Manager::ServerConfigurationManager::WEAPON_SKILL_DAMAGE_MULTIPLIER );
    double minDamage = ( character->combatAttributes().attack() );
    double damage = rollRange( minDamage, maxDamage ) - creature->defense();
    damage = std::max( 1.0, damage );

    double newHealth = creature->vitals().health() - damage;
    newHealth = std::max( 0.0, newHealth );
    creature->vitals().setHealth( newHealth );

    double xpWeaponSkill = damage;
    _progressionSystem.applyExperience( sessionId, character, weaponSkill, xpWeaponSkill );

    std::cout << "CombatSystem::computeHitDamage"
              << " [CHARACTER] " << character->name()
              << " [DAMAGE] " << damage
              << " [CREATURE] " << creature->name()
              << " [HP LEFT]: " << creature->vitals().health() << std::endl;
}

void CombatSystem::computeHitDamage( Model::Creature* creature, const std::string& sessionId, Model::Character* character ) {
    double newStamina = creature->vitals().stamina() - 1;
    newStamina = std::max( 0.0, newStamina );
    creature->vitals().setStamina( newStamina );

    bool hasShieldEquipped = ( character->equipment().offhand().item() && character->equipment().offhand().item()->category() == "shield" );

    double maxCreatureAttack = creature->attack();
    double damage = rollRange( 0, maxCreatureAttack );

    damage -= character->combatAttributes().defense();
    damage = std::max( 0.0, damage );

    if ( hasShieldEquipped ) {
        int shieldLevel = character->skills().skillLevel( Model::SkillType::SHIELD_MASTERY );
        double blockChance = 0.5 + ( 0.005 * ( shieldLevel - creature->accuracy() ) );
        blockChance = std::clamp( blockChance, 0.05, 0.95 );

        if ( rollChance( blockChance ) ) {
            _progressionSystem.applyExperience( sessionId, character, Model::SkillType::SHIELD_MASTERY, creature->accuracy() );

            double reduction = 0.5 + ( 0.005 * shieldLevel );
            reduction = std::clamp( reduction, 0.05, 1.0 );
            damage *= ( 1.0 - reduction );
        }

    } else {
        double evasionChance = ( 0.5 - ( 0.005 * creature->accuracy() ) );
        evasionChance = std::clamp( evasionChance, 0.05, 0.95 );

        if ( rollChance( evasionChance ) ) {
            return;
        }
    }

    double newHealth = character->vitals().health() - damage;
    newHealth = std::max( 0.0, newHealth );
    character->vitals().setHealth( newHealth );

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

    int invocationLevel = character->skills().skillLevel( Model::SkillType::INVOCATION );

    _progressionSystem.applyExperience( sessionId, character, Model::SkillType::INVOCATION, characterSpell->spell()->manaCost() );

    double hitChance = 0.5 + 0.005 * ( invocationLevel - creature->evasion() );
    hitChance = std::clamp( hitChance, 0.05, 0.95 );
    if ( !rollChance( hitChance ) ) {
        return;
    }

    double maxDamage = characterSpell->spell()->effect().value() + ( invocationLevel * Manager::ServerConfigurationManager::MAGIC_SKILL_DAMAGE_MULTIPLIER );
    double minDamage = characterSpell->spell()->effect().value();
    double damage = rollRange( minDamage, maxDamage );

    double newHealth = creature->vitals().health() - damage;
    newHealth = std::max( 0.0, newHealth );
    creature->vitals().setHealth( newHealth );

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

Model::SkillType CombatSystem::combatSkill( Model::Character* character ) {
    const Model::Item* weapon = character->equipment().weapon().item();

    Model::SkillType skill = combatSkillByWeapon( weapon );

    return skill;
}

Model::SkillType CombatSystem::combatSkillByWeapon( const Model::Item* weapon ) {
    if ( !weapon ) {
        return Model::SkillType::FIST_MASTERY;
    }

    const std::string& category = weapon->category();
    if ( category == "sword" ) {
        return Model::SkillType::SWORD_MASTERY;

    } else if ( category == "axe" ) {
        return Model::SkillType::AXE_MASTERY;

    } else if ( category == "dagger" ) {
        return Model::SkillType::DAGGER_MASTERY;

    } else {
        std::cerr << "CombatSystem::combatSkillByWeapon Unknow weapon category: " << category << std::endl;
    }

    return Model::SkillType::FIST_MASTERY;
}

} // namespace Core::System
