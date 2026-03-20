#include "CharacterStageController.h"

namespace Engine {

CharacterStageController::CharacterStageController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                    Domain::Character& character ) :
    CharacterController( eventBus, messageSender ),
    _characterStage( character.stage() ) {

    _eventBus.subscribe( CharacterEventType::CREATURE_KILLED, [ this ]( const CharacterEvent& event ) {
        onCreatureKilled( event );
    } );
}

void CharacterStageController::onEnterWorld() {
    _messageSender.sendMessage( MessageSenderType::CHARACTER_STAGE, _characterStage.toJson() );
}

void CharacterStageController::onLeaveWorld() {
}

void CharacterStageController::onTick() {
}

void CharacterStageController::handleMessage( MessageReceiverType type, const Json::Value& payload ) {
    switch ( type ) {
    case MessageReceiverType::CHARACTER_STAGE_NEXT:
        _characterStage.setStageLevel( _characterStage.stageLevel() + 1 );
        _characterStage.setCompleted( false );

        _messageSender.sendMessage( MessageSenderType::CHARACTER_STAGE, _characterStage.toJson() );
    default:
        break;
    }
}

void CharacterStageController::updateStageCompletion() {
    for ( const auto& objective : _characterStage.objectives() ) {
        if ( objective.currentAmount() < objective.stageAmount() ) {
            return;
        }
    }
    _characterStage.setCompleted( true );
    _messageSender.sendMessage( MessageSenderType::CHARACTER_STAGE, _characterStage.toJson() );
}

void CharacterStageController::onCreatureKilled( const CharacterEvent& event ) {
    const Json::Value& payload = event.payload();
    if ( !payload.isMember( "creature" ) ) {
        return;
    }

    const std::string creatureId = payload[ "creature" ].asString();

    bool updated = false;

    auto& objectives = _characterStage.objectives();

    for ( auto& objective : objectives ) {
        // TODO: Change type from string to enum
        if ( objective.type() != "KILL" ) {
            continue;
        }

        if ( objective.target() != creatureId ) {
            continue;
        }

        int current = objective.currentAmount();
        int required = objective.stageAmount();

        if ( current >= required ) {
            continue;
        }

        objective.setCurrentAmount( current + 1 );
        updated = true;
    }

    if ( updated ) {
        updateStageCompletion();
    }
}

} // namespace Engine
