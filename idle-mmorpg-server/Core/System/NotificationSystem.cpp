#include "NotificationSystem.h"

#include <Commons/ActionsHelper.h>

namespace Core::System {

NotificationSystem::NotificationSystem() :
    _sender() {
}

void NotificationSystem::notifyFullCharacter( const std::string& sessionId, Model::Character* character ) {
    Json::Value characterJson = character->toJson();
    characterJson[ "action" ] = character->action().toJson();
    characterJson[ "attributes" ] = character->attributes().toJson();
    characterJson[ "coordinates" ] = character->coordinates().toJson();
    characterJson[ "inventory" ] = character->inventory().toJson();
    characterJson[ "equipament" ] = character->equipment().toJson();
    characterJson[ "progression" ] = character->progression().toJson();
    characterJson[ "skills" ] = character->skills().toJson();
    characterJson[ "vitals" ] = character->vitals().toJson();
    characterJson[ "wallet" ] = character->wallet().toJson();
    _sender.send( sessionId, Message::MessageSenderType::CHARACTER_UPDATE, characterJson );
}

void NotificationSystem::notifyCharacterAttributes( const std::string& sessionId, Model::Character* character ) {
    Json::Value payload;
    payload[ "attributes" ] = character->attributes().toJson();
    _sender.send( sessionId, Message::MessageSenderType::CHARACTER_UPDATE_ATTRIBUTES, payload );
}

void NotificationSystem::notifyCharacterProgression( const std::string& sessionId, Model::Character* character ) {
    Json::Value payload;
    payload[ "progression" ] = character->progression().toJson();
    _sender.send( sessionId, Message::MessageSenderType::CHARACTER_UPDATE_PROGRESSION, payload );
}

void NotificationSystem::notifyCharacterSkills( const std::string& sessionId, Model::Character* character ) {
    Json::Value payload;
    payload[ "skills" ] = character->skills().toJson();
    _sender.send( sessionId, Message::MessageSenderType::CHARACTER_UPDATE_SKILLS, payload );
}

void NotificationSystem::notifyCharacterVitals( const std::string& sessionId, Model::Character* character ) {
    Json::Value payload;
    payload[ "vitals" ] = character->vitals().toJson();
    _sender.send( sessionId, Message::MessageSenderType::CHARACTER_UPDATE_VITALS, payload );
}

void NotificationSystem::notifyCurrentAction( const std::string& sessionId, Model::Character* character ) {
    Json::Value payloadCurrentAction;
    payloadCurrentAction[ "action" ] = character->action().toJson();
    _sender.send( sessionId, Message::MessageSenderType::CHARACTER_UPDATE_ACTION, payloadCurrentAction );
}

void NotificationSystem::notifyCurrentCoordinates( const std::string& sessionId, Model::Character* character ) {
    Json::Value payloadCurrentCoordinates;
    payloadCurrentCoordinates[ "coordinates" ] = character->coordinates().toJson();
    _sender.send( sessionId, Message::MessageSenderType::CHARACTER_UPDATE_COORDINATES, payloadCurrentCoordinates );
}

void NotificationSystem::notifyFullLocation( const std::string& sessionId, const Model::Location* location ) {
    Json::Value payloadLocation;
    payloadLocation[ "location" ] = location->toJson();
    _sender.send( sessionId, Message::MessageSenderType::LOCATION_UPDATE_POSITION, payloadLocation );
}

void NotificationSystem::notifyLocationActions( const std::string& sessionId, Model::Character* character, const Model::Location* location ) {
    Json::Value payloadLocationActions;
    Json::Value availableActions;

    for ( auto action : location->actions() ) {
        if ( Commons::ActionsHelper::canCharacterPerformAction( character, action ) ) {
            availableActions.append( action.toJson() );
        }
    }

    payloadLocationActions[ "actions" ] = availableActions;
    _sender.send( sessionId, Message::MessageSenderType::LOCATION_UPDATE_ACTIONS, payloadLocationActions );
}

} // namespace Core::System
