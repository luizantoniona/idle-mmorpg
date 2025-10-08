#include "RegenerationSystem.h"

#include <iostream>

#include <Commons/Singleton.h>
#include <Core/Manager/ServerConfigurationManager.h>
#include <Core/System/NotificationSystem.h>
#include <Core/System/ProgressionSystem.h>
#include <Helper/DecimalHelper.h>

namespace Core::System {

void RegenerationSystem::processRegeneration( const std::string& sessionId, Model::Character* character ) {
    auto& characterVitals = character->vitals();

    if ( characterVitals.health() >= characterVitals.maxHealth() && characterVitals.mana() >= characterVitals.maxMana() && characterVitals.stamina() >= characterVitals.maxStamina() ) {
        return;
    }

    if ( characterVitals.regenCounter() < characterVitals.regenDuration() ) {
        characterVitals.setRegenCounter( characterVitals.regenCounter() + 1 );
        return;
    }

    characterVitals.setRegenCounter( 0 );

    computeRegeneration( sessionId, character );
}

void RegenerationSystem::computeRegeneration( const std::string& sessionId, Model::Character* character, double baseRegenerationValue ) {
    auto& characterVitals = character->vitals();

    const double vitalityLevel = character->skills().skillLevel( "vitality" );
    const double enduranceLevel = character->skills().skillLevel( "endurance" );
    const double meditationLevel = character->skills().skillLevel( "meditation" );

    const double healthRegen = baseRegenerationValue + ( vitalityLevel * Core::Manager::ServerConfigurationManager::VITAL_SKILL_REGENERATION_MULTIPLIER );
    const double staminaRegen = baseRegenerationValue + ( enduranceLevel * Core::Manager::ServerConfigurationManager::VITAL_SKILL_REGENERATION_MULTIPLIER );
    const double manaRegen = baseRegenerationValue + ( meditationLevel * Core::Manager::ServerConfigurationManager::VITAL_SKILL_REGENERATION_MULTIPLIER );

    double newHealth = characterVitals.health() + Helper::DecimalHelper::roundDecimals( healthRegen );
    if ( newHealth > characterVitals.maxHealth() ) {
        newHealth = characterVitals.maxHealth();
    }
    characterVitals.setHealth( newHealth );

    double newStamina = characterVitals.stamina() + Helper::DecimalHelper::roundDecimals( staminaRegen );
    if ( newStamina > characterVitals.maxStamina() ) {
        newStamina = characterVitals.maxStamina();
    }
    characterVitals.setStamina( newStamina );

    double newMana = characterVitals.mana() + Helper::DecimalHelper::roundDecimals( manaRegen );
    if ( newMana > characterVitals.maxMana() ) {
        newMana = characterVitals.maxMana();
    }
    characterVitals.setMana( newMana );

    NotificationSystem::notifyCharacterVitals( sessionId, character );
}

void RegenerationSystem::processSpellsCooldown( const std::string& sessionId, Model::Character* character ) {
    auto& characterSpells = character->spells();
    const int tickRate = Commons::Singleton<Core::Manager::ServerConfigurationManager>::instance().tickRate();
    bool changed = false;

    for ( auto& spell : characterSpells.healingSpells() ) {
        if ( spell.count() < spell.spell()->cooldown() ) {
            if ( spell.count() % tickRate == 0 ) {
                changed = true;
            }

            spell.setCount( spell.count() + 1 );

            if ( spell.count() == spell.spell()->cooldown() ) {
                changed = true;
            }
        }
    }

    for ( auto& spell : characterSpells.attackSpells() ) {
        if ( spell.count() < spell.spell()->cooldown() ) {
            if ( spell.count() % tickRate == 0 ) {
                changed = true;
            }

            spell.setCount( spell.count() + 1 );

            if ( spell.count() == spell.spell()->cooldown() ) {
                changed = true;
            }
        }
    }

    if ( changed ) {
        NotificationSystem::notifyCharacterSpells( sessionId, character );
    }
}

void RegenerationSystem::castHealingSpell( const std::string& sessionId, Model::Character* character, const std::string& spellId ) {
    auto characterSpell = character->spells().healingSpell( spellId );
    if ( !characterSpell ) {
        return;
    }

    auto spell = characterSpell->spell();
    if ( characterSpell->count() < spell->cooldown() ) {
        return;
    }

    if ( character->vitals().mana() < spell->manaCost() ) {
        return;
    }

    double newMana = character->vitals().mana() - spell->manaCost();
    newMana = std::max( 0.0, newMana );
    character->vitals().setMana( newMana );

    characterSpell->setCount( 0 );

    const double restorationLevel = character->skills().skillLevel( "restoration" );
    double heal = spell->effect().value();

    double newHealth = std::min( character->vitals().health() + heal, character->vitals().maxHealth() );
    character->vitals().setHealth( newHealth );

    ProgressionSystem().applyExperience( sessionId, character, "restoration", spell->manaCost() );
    NotificationSystem::notifyCharacterVitals( sessionId, character );

    std::cout << character->name() << " casts " << spell->name() << " healing " << heal << " health." << std::endl;
}

} // namespace Core::System
