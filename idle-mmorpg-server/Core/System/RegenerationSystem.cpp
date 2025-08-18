#include "RegenerationSystem.h"

#include <Commons/DecimalHelper.h>
#include <Core/System/NotificationSystem.h>

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

    const double healthRegen = characterVitals.healthRegen() + character->attributes().constitution() * 0.1;
    const double staminaRegen = characterVitals.staminaRegen() + character->attributes().constitution() * 0.1;
    const double manaRegen = characterVitals.manaRegen() + character->attributes().intelligence() * 0.1;

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

} // namespace Core::System
