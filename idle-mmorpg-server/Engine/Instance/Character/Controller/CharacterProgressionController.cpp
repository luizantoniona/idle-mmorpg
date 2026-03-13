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

void CharacterProgressionController::applyLevelUp() {
    Json::Value healthPayload;
    healthPayload[ "value" ] = _configurationManager.vitalsRate().health;
    _eventBus.publish( CharacterEvent( CharacterEventType::VITAL_MAX_HEALTH_GAINED, healthPayload ) );

    Json::Value manaPayload;
    manaPayload[ "value" ] = _configurationManager.vitalsRate().mana;
    _eventBus.publish( CharacterEvent( CharacterEventType::VITAL_MAX_MANA_GAINED, manaPayload ) );

    Json::Value staminaPayload;
    staminaPayload[ "value" ] = _configurationManager.vitalsRate().stamina;
    _eventBus.publish( CharacterEvent( CharacterEventType::VITAL_MAX_STAMINA_GAINED, staminaPayload ) );
}

void CharacterProgressionController::onProgressionExperienceGained( const CharacterEvent& event ) {
    const Json::Value& payload = event.payload();
    if ( !payload.isMember( "value" ) ) {
        return;
    }

    const int xpGained = payload[ "value" ].asInt();
    if ( xpGained <= 0 ) {
        return;
    }

    int newXp = _characterProgression.experience() + xpGained;
    int xpNeeded = _characterProgression.experienceForNextLevel( _characterProgression.level() );

    while ( newXp >= xpNeeded ) {

        newXp -= xpNeeded;
        _characterProgression.setLevel( _characterProgression.level() + 1 );

        applyLevelUp();

        xpNeeded = _characterProgression.experienceForNextLevel( _characterProgression.level() );

        Json::Value payload;
        _eventBus.publish( CharacterEvent( CharacterEventType::PROGRESSION_LEVEL_GAINED, payload ) );
    }

    _characterProgression.setExperience( newXp );

    _messageSender.sendMessage( MessageSenderType::CHARACTER_PROGRESSION, _characterProgression.toJson() );
}

} // namespace Engine
