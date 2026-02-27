#include "CharacterVitalsController.h"

namespace Engine {

CharacterVitalsController::CharacterVitalsController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                      Domain::Character& character ) :
    CharacterController( eventBus, messageSender ),
    _characterVitals( character.vitals() ) {

    _eventBus.subscribe( CharacterEventType::VITAL_MAX_GAINED, [ this ]( const CharacterEvent& event ) {
        onVitalMaxGained( event );
    } );
}

void CharacterVitalsController::onEnterWorld() {
    _messageSender.sendMessage( MessageSenderType::CHARACTER_VITALS, _characterVitals.toJson() );
}

void CharacterVitalsController::onLeaveWorld() {
}

void CharacterVitalsController::onTick() {
}

void CharacterVitalsController::onVitalMaxGained( const CharacterEvent& event ) {
    const Json::Value& payload = event.payload();
    if ( !payload.isMember( "value" ) || !payload.isMember( "vital" ) ) {
        return;
    }

    const std::string vitalType = payload[ "vital" ].asString();

    if ( vitalType == "health" ) {
        _characterVitals.setMaxHealth( _characterVitals.maxHealth() + payload[ "value" ].asDouble() );

    } else if ( vitalType == "mana" ) {
        _characterVitals.setMaxMana( _characterVitals.maxMana() + payload[ "value" ].asDouble() );

    } else if ( vitalType == "stamina" ) {
        _characterVitals.setMaxStamina( _characterVitals.maxStamina() + payload[ "value" ].asDouble() );

    } else {
        std::cerr << "CharacterVitalsController::onVitalMaxGained Unknown vital id: " << vitalType << std::endl;
    }

    _messageSender.sendMessage( MessageSenderType::CHARACTER_VITALS, _characterVitals.toJson() );
}

} // namespace Engine
