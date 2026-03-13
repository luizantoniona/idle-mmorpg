#include "CharacterVitalsController.h"

namespace Engine {

CharacterVitalsController::CharacterVitalsController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                      Domain::Character& character,
                                                      Manager::ServerConfigurationManager& configurationManager ) :
    CharacterController( eventBus, messageSender ),
    _character( character ),
    _characterVitals( character.vitals() ),
    _configurationManager( configurationManager ) {

    _eventBus.subscribe( CharacterEventType::VITAL_MAX_HEALTH_GAINED, [ this ]( const CharacterEvent& event ) {
        onVitalMaxHealthGained( event );
    } );
    _eventBus.subscribe( CharacterEventType::VITAL_MAX_MANA_GAINED, [ this ]( const CharacterEvent& event ) {
        onVitalMaxManaGained( event );
    } );
    _eventBus.subscribe( CharacterEventType::VITAL_MAX_STAMINA_GAINED, [ this ]( const CharacterEvent& event ) {
        onVitalMaxStaminaGained( event );
    } );
    _eventBus.subscribe( CharacterEventType::VITAL_HEALTH_CHANGED, [ this ]( const CharacterEvent& event ) {
        onVitalHealthChanged( event );
    } );
    _eventBus.subscribe( CharacterEventType::VITAL_MANA_CHANGED, [ this ]( const CharacterEvent& event ) {
        onVitalManaChanged( event );
    } );
    _eventBus.subscribe( CharacterEventType::VITAL_STAMINA_CHANGED, [ this ]( const CharacterEvent& event ) {
        onVitalStaminaChanged( event );
    } );
}

void CharacterVitalsController::onEnterWorld() {
    _characterVitals.setRegenDuration( _configurationManager.tickRate() );

    _messageSender.sendMessage( MessageSenderType::CHARACTER_VITALS, _characterVitals.toJson() );
}

void CharacterVitalsController::onLeaveWorld() {
}

void CharacterVitalsController::onTick() {
    if ( _character.combat().isInCombat() ) {
        return;
    }

    int counter = _characterVitals.regenCounter() + 1;
    _characterVitals.setRegenCounter( counter );

    if ( counter < _characterVitals.regenDuration() ) {
        return;
    }

    _characterVitals.setRegenCounter( 0 );

    bool changed = false;

    if ( _characterVitals.health() < _characterVitals.maxHealth() ) {
        // TODO: Adjust Regeneration Hate
        _characterVitals.modifyHealth( 1.0 );
        changed = true;
    }

    if ( _characterVitals.mana() < _characterVitals.maxMana() ) {
        // TODO: Adjust Regeneration Hate
        _characterVitals.modifyMana( 1.0 );
        changed = true;
    }

    if ( _characterVitals.stamina() < _characterVitals.maxStamina() ) {
        // TODO: Adjust Regeneration Hate
        _characterVitals.modifyStamina( 1.0 );
        changed = true;
    }

    if ( changed ) {
        _messageSender.sendMessage( MessageSenderType::CHARACTER_VITALS, _characterVitals.toJson() );
    }
}

void CharacterVitalsController::onVitalMaxHealthGained( const CharacterEvent& event ) {
    const Json::Value& payload = event.payload();
    if ( !payload.isMember( "value" ) ) {
        return;
    }

    const double value = payload[ "value" ].asDouble();
    _characterVitals.modifyMaxHealth( value );
    _messageSender.sendMessage( MessageSenderType::CHARACTER_VITALS, _characterVitals.toJson() );
}

void CharacterVitalsController::onVitalMaxManaGained( const CharacterEvent& event ) {
    const Json::Value& payload = event.payload();
    if ( !payload.isMember( "value" ) ) {
        return;
    }

    const double value = payload[ "value" ].asDouble();
    _characterVitals.modifyMaxMana( value );
    _messageSender.sendMessage( MessageSenderType::CHARACTER_VITALS, _characterVitals.toJson() );
}

void CharacterVitalsController::onVitalMaxStaminaGained( const CharacterEvent& event ) {
    const Json::Value& payload = event.payload();
    if ( !payload.isMember( "value" ) ) {
        return;
    }

    const double value = payload[ "value" ].asDouble();
    _characterVitals.modifyMaxStamina( value );
    _messageSender.sendMessage( MessageSenderType::CHARACTER_VITALS, _characterVitals.toJson() );
}

void CharacterVitalsController::onVitalHealthChanged( const CharacterEvent& event ) {
    const Json::Value& payload = event.payload();
    if ( !payload.isMember( "value" ) ) {
        return;
    }

    const double value = payload[ "value" ].asDouble();
    _characterVitals.modifyHealth( value );
    _messageSender.sendMessage( MessageSenderType::CHARACTER_VITALS, _characterVitals.toJson() );

    if ( value < 0 ) {
        Json::Value xpPayload;
        xpPayload[ "skill" ] = static_cast<int>( Domain::SkillType::VITALITY );
        xpPayload[ "experience" ] = std::abs( value );
        _eventBus.publish( CharacterEvent( CharacterEventType::SKILL_EXPERIENCE_GAINED, xpPayload ) );
    }
}

void CharacterVitalsController::onVitalManaChanged( const CharacterEvent& event ) {
    const Json::Value& payload = event.payload();
    if ( !payload.isMember( "value" ) ) {
        return;
    }

    const double value = payload[ "value" ].asDouble();
    _characterVitals.modifyMana( value );
    _messageSender.sendMessage( MessageSenderType::CHARACTER_VITALS, _characterVitals.toJson() );

    if ( value < 0 ) {
        Json::Value xpPayload;
        xpPayload[ "skill" ] = static_cast<int>( Domain::SkillType::MEDITATION );
        xpPayload[ "experience" ] = std::abs( value );
        _eventBus.publish( CharacterEvent( CharacterEventType::SKILL_EXPERIENCE_GAINED, xpPayload ) );
    }
}

void CharacterVitalsController::onVitalStaminaChanged( const CharacterEvent& event ) {
    const Json::Value& payload = event.payload();
    if ( !payload.isMember( "value" ) ) {
        return;
    }

    const double value = payload[ "value" ].asDouble();
    _characterVitals.modifyStamina( value );
    _messageSender.sendMessage( MessageSenderType::CHARACTER_VITALS, _characterVitals.toJson() );

    if ( value < 0 ) {
        Json::Value xpPayload;
        xpPayload[ "skill" ] = static_cast<int>( Domain::SkillType::ENDURANCE );
        xpPayload[ "experience" ] = std::abs( value );
        _eventBus.publish( CharacterEvent( CharacterEventType::SKILL_EXPERIENCE_GAINED, xpPayload ) );
    }
}

} // namespace Engine
