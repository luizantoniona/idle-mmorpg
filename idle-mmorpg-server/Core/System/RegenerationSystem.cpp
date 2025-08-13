#include "RegenerationSystem.h"

#include <Commons/DecimalHelper.h>
#include <Core/System/NotificationSystem.h>

namespace Core::System {

void RegenerationSystem::computeRegeneration( const std::string& sessionId, Model::Character* character ) {
    auto& characterVitals = character->vitals();

    if ( characterVitals.health() >= characterVitals.maxHealth() && characterVitals.mana() >= characterVitals.maxMana() && characterVitals.stamina() >= characterVitals.maxStamina() ) {
        return;
    }

    auto& combatAction = character->combatAction();

    if ( combatAction.regenCounter() < combatAction.regenDuration() ) {
        combatAction.setRegenCounter( combatAction.regenCounter() + 1 );
        return;
    }

    combatAction.setRegenCounter( 0 );

    const double healthRegen = characterVitals.healthRegen() + character->attributes().constitution() * 0.1;
    const double staminaRegen = characterVitals.staminaRegen() + character->attributes().constitution() * 0.1;
    const double manaRegen = characterVitals.manaRegen() + character->attributes().intelligence() * 0.1;

    double newHealth = characterVitals.health() + Commons::DecimalHelper::roundDecimals( healthRegen );
    if ( newHealth > characterVitals.maxHealth() ) {
        newHealth = characterVitals.maxHealth();
    }
    characterVitals.setHealth( newHealth );

    double newStamina = characterVitals.stamina() + Commons::DecimalHelper::roundDecimals( staminaRegen );
    if ( newStamina > characterVitals.maxStamina() ) {
        newStamina = characterVitals.maxStamina();
    }
    characterVitals.setStamina( newStamina );

    double newMana = characterVitals.mana() + Commons::DecimalHelper::roundDecimals( manaRegen );
    if ( newMana > characterVitals.maxMana() ) {
        newMana = characterVitals.maxMana();
    }
    characterVitals.setMana( newMana );

    NotificationSystem::notifyCharacterVitals( sessionId, character );
}

} // namespace Core::System
