#include "CharacterCombatController.h"

namespace Engine {

CharacterCombatController::CharacterCombatController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                      Domain::Character& character,
                                                      Manager::ServerConfigurationManager& configurationManager ) :
    CharacterController( eventBus, messageSender ),
    _character( character ),
    _characterCombat( character.combat() ),
    _configurationManager( configurationManager ) {

    _eventBus.subscribe( CharacterEventType::EQUIPMENT_ITEM_EQUIPPED, [ this ]( const CharacterEvent& event ) {
        onEquipmentEquipped( event );
    } );
}

void CharacterCombatController::onEnterWorld() {
}

void CharacterCombatController::onLeaveWorld() {
}

void CharacterCombatController::onTick() {
}

void CharacterCombatController::handleMessage( MessageReceiverType type, const Json::Value& payload ) {
}

void CharacterCombatController::onEquipmentEquipped( const CharacterEvent& event ) {
    auto& characterEquipment = _character.equipment();

    const Domain::Item* characterWeapon = characterEquipment.weapon().item();
    const Domain::Item* characterOffHand = characterEquipment.offhand().item();

    if ( characterWeapon ) {
        // TODO: Recompute _characterCombat.attackDuration -> based on weapon
    }

    if ( characterOffHand ) {
        // TODO: Recompute _characterCombat.attackDuration -> based on offhand
    }
}

} // namespace Engine
