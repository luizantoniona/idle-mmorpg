#include "CombatSystem.h"

#include <algorithm>
#include <iostream>

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
    std::cout << "CombatSystem::computeHitDamage [CHARACTER]" << character->name() << " [CREATURE] " << creature->name() << std::endl;

    double hitChance = character->combatAttributes().accuracy() + character->attributes().dexterity() - creature->evasion();
    hitChance = std::clamp( hitChance, 0.1, 0.95 );

    double roll = static_cast<double>( rand() ) / RAND_MAX;
    if ( roll > hitChance ) {
        std::cout << "Attack missed!" << std::endl;
        return;
    }

    double damage = character->combatAttributes().attack() + character->attributes().strength() - creature->defense();
    damage = std::max( 0.0, damage );

    double newHealth = creature->vitals().health() - damage;
    newHealth = std::max( 0.0, newHealth );
    creature->vitals().setHealth( newHealth );

    _progressionSystem.applyExperience( sessionId, character, combatSkill( character ), damage );

    std::cout << "Hit for " << damage << " damage. Creature HP left: " << creature->vitals().health() << std::endl;
}

void CombatSystem::computeHitDamage( Model::Creature* creature, const std::string& sessionId, Model::Character* character ) {
    std::cout << "CombatSystem::computeHitDamage [CREATURE]" << creature->name() << " [CHARACTER] " << character->name() << std::endl;

    double hitChance = creature->accuracy() - character->combatAttributes().evasion() - character->attributes().dexterity();
    hitChance = std::clamp( hitChance, 0.1, 0.95 );

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
    damage = std::max( 0.0, damage );

    double newHealth = character->vitals().health() - damage;
    newHealth = std::max( 0.0, newHealth );
    character->vitals().setHealth( newHealth );

    _progressionSystem.applyExperience( sessionId, character, "resilience", damage );

    std::cout << "Hit for " << damage << " damage. Character HP left: " << character->vitals().health() << std::endl;
}

void CombatSystem::computeRegeneration( const std::string& sessionId, Model::Character* character ) {
    const double healthRegen = character->vitals().healthRegen() + character->attributes().constitution() * 0.1;
    const double staminaRegen = character->vitals().staminaRegen() + character->attributes().constitution() * 0.1;
    const double manaRegen = character->vitals().manaRegen() + character->attributes().constitution() * 0.1;

    int newHealth = character->vitals().health() + healthRegen;
    if ( newHealth > character->vitals().maxHealth() ) {
        newHealth = character->vitals().maxHealth();
    }
    character->vitals().setHealth( newHealth );

    int newStamina = character->vitals().stamina() + staminaRegen;
    if ( newStamina > character->vitals().maxStamina() ) {
        newStamina = character->vitals().maxStamina();
    }
    character->vitals().setStamina( newStamina );

    int newMana = character->vitals().mana() + manaRegen;
    if ( newMana > character->vitals().maxMana() ) {
        newMana = character->vitals().maxMana();
    }
    character->vitals().setMana( newMana );
}

void CombatSystem::computeLoot( std::unordered_map<std::string, Model::Character*> characters, std::vector<std::unique_ptr<Model::Creature>> creatures ) {
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

                // receiver->inventory().addItem( lootEntry.itemId, lootEntry.quantity );
                // Core::System::NotificationSystem::notifyInventory
                std::cout << "[CHARACTER] " << receiver->name() << " [QUANTITY] " << lootEntry.amount() << " [ITEM] " << lootEntry.id() << std::endl;
            }
        }
    }
}

void CombatSystem::computeExperience( std::unordered_map<std::string, Model::Character*> characters, std::vector<std::unique_ptr<Model::Creature>> creatures ) {
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
            // _progressionSystem.addExperience( sessionId, character, xpPerCharacter );
            std::cout << "[CHARACTER] " << character->name() << " [XP] " << xpPerCharacter << " XP.\n";
        }
    }
}

std::string CombatSystem::combatSkill( Model::Character* character ) {

    // TODO O que acontece se estiver com duas armas diferentes?
    // Quais skills upar?
    // TODO Dividir a XP entre todas?

    // if ( character->equipment().leftHand().id().empty() || character->equipment().rightHand().id().empty() ) {
    //     std::string weaponType = character->equipment();
    //     if ( weaponType == "sword" )
    //         return "swordsmanship";
    //     if ( weaponType == "bow" )
    //         return "archery";
    //     // ... outros tipos de armas
    // }

    return "unarmed";
}

} // namespace Core::System
