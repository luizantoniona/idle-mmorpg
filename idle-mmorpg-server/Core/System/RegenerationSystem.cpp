#include "RegenerationSystem.h"

#include <iostream>

#include <Commons/Singleton.h>
#include <Core/Manager/ServerConfigurationManager.h>
#include <Core/System/NotificationSystem.h>
#include <Core/System/ProgressionSystem.h>
#include <Helper/DecimalHelper.h>

namespace Core::System {

void RegenerationSystem::computeRegeneration( const std::string& sessionId, Model::Character* character ) {
    auto& characterVitals = character->vitals();

    if ( characterVitals.health() >= characterVitals.maxHealth() && characterVitals.mana() >= characterVitals.maxMana() && characterVitals.stamina() >= characterVitals.maxStamina() ) {
        return;
    }

    if ( characterVitals.regenCounter() < characterVitals.regenDuration() ) {
        characterVitals.setRegenCounter( characterVitals.regenCounter() + 1 );
        return;
    }

    characterVitals.setRegenCounter( 0 );

    const double healthRegen = std::max( 1.0, character->attributes().constitution() );
    const double staminaRegen = std::max( 1.0, character->attributes().dexterity() );
    const double manaRegen = std::max( 1.0, character->attributes().intelligence() );

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

void RegenerationSystem::computeSpellsCooldown( const std::string& sessionId, Model::Character* character ) {
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

    double heal = spell->effect().value() + character->attributes().wisdom();

    double newHealth = std::min( character->vitals().health() + heal, character->vitals().maxHealth() );
    character->vitals().setHealth( newHealth );

    ProgressionSystem().applyExperience( sessionId, character, "focus", heal );
    NotificationSystem::notifyCharacterVitals( sessionId, character );

    std::cout << character->name() << " casts " << spell->name() << " healing " << heal << " health." << std::endl;
}

} // namespace Core::System
