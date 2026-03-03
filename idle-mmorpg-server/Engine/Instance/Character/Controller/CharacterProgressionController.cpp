#include "CharacterProgressionController.h"

namespace Engine {

CharacterProgressionController::CharacterProgressionController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                                Domain::Character& character,
                                                                Manager::ServerConfigurationManager& configurationManager ) :
    CharacterController( eventBus, messageSender ),
    _characterProgression( character.progression() ),
    _configurationManager( configurationManager ) {

    _eventBus.subscribe( CharacterEventType::PROGRESSION_EXPERIENCE_GAINED, [ this ]( const CharacterEvent& event ) {
        onProgressionExperienceGained( event );
    } );
}

void CharacterProgressionController::onEnterWorld() {
    _characterProgression.setBaseExperience( _configurationManager.baseExperience() );
    _characterProgression.setGrowthRate( _configurationManager.growthRate() );

    _messageSender.sendMessage( MessageSenderType::CHARACTER_PROGRESSION, _characterProgression.toJson() );
}

void CharacterProgressionController::onLeaveWorld() {
}

void CharacterProgressionController::onTick() {
}

void CharacterProgressionController::onProgressionExperienceGained( const CharacterEvent& event ) {
    const Json::Value& payload = event.payload();
    if ( !payload.isMember( "value" ) ) {
        return;
    }

    const int value = payload[ "value" ].asInt();

    // TODO: Apply experience and level up if needed, and maxStats improvement;

    _messageSender.sendMessage( MessageSenderType::CHARACTER_PROGRESSION, _characterProgression.toJson() );
}

} // namespace Engine
