#include "RegenerationSystem.h"

#include <iostream>

#include <Commons/DecimalHelper.h>
#include <Core/System/NotificationSystem.h>
#include <Core/System/ProgressionSystem.h>

namespace Core::System {

void RegenerationSystem::computeRegeneration( const std::string& sessionId, Model::Character* character ) {
    auto& characterVitals = character->vitals();

    if ( characterVitals.health() >= characterVitals.fullHealth() && characterVitals.mana() >= characterVitals.fullMana() && characterVitals.stamina() >= characterVitals.fullStamina() ) {
        return;
    }

    if ( characterVitals.regenCounter() < characterVitals.regenDuration() ) {
        characterVitals.setRegenCounter( characterVitals.regenCounter() + 1 );
        return;
    }

    characterVitals.setRegenCounter( 0 );

    const double healthRegen = characterVitals.healthRegen() + character->attributes().constitution();
    const double staminaRegen = characterVitals.staminaRegen() + character->attributes().dexterity();
    const double manaRegen = characterVitals.manaRegen() + character->attributes().intelligence();

    double newHealth = characterVitals.health() + Commons::DecimalHelper::roundDecimals( healthRegen );
    if ( newHealth > characterVitals.fullHealth() ) {
        newHealth = characterVitals.fullHealth();
    }
    characterVitals.setHealth( newHealth );

    double newStamina = characterVitals.stamina() + Commons::DecimalHelper::roundDecimals( staminaRegen );
    if ( newStamina > characterVitals.fullStamina() ) {
        newStamina = characterVitals.fullStamina();
    }
    characterVitals.setStamina( newStamina );

    double newMana = characterVitals.mana() + Commons::DecimalHelper::roundDecimals( manaRegen );
    if ( newMana > characterVitals.fullMana() ) {
        newMana = characterVitals.fullMana();
    }
    characterVitals.setMana( newMana );

    NotificationSystem::notifyCharacterVitals( sessionId, character );
}

void RegenerationSystem::computeSpellsCooldown( const std::string& sessionId, Model::Character* character ) {
    auto& characterSpells = character->spells();

    bool changed = false;

    for ( auto& spell : characterSpells.healingSpells() ) {
        if ( spell.count() < spell.spell()->cooldown() ) {
            spell.setCount( spell.count() + 1 );
            changed = true;
        }
    }

    for ( auto& spell : characterSpells.attackSpells() ) {
        if ( spell.count() < spell.spell()->cooldown() ) {
            spell.setCount( spell.count() + 1 );
            changed = true;
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

    double newHealth = std::min( character->vitals().health() + heal, character->vitals().fullHealth() );
    character->vitals().setHealth( newHealth );

    ProgressionSystem().applyExperience( sessionId, character, "clarity", heal );

    std::cout << character->name() << " casts " << spell->name() << " healing " << heal << " health." << std::endl;
}

} // namespace Core::System
