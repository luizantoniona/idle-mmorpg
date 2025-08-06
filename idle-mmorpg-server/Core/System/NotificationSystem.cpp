#include "NotificationSystem.h"

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
    characterJson[ "equipament" ] = character->equipament().toJson();
    characterJson[ "progression" ] = character->progression().toJson();
    characterJson[ "skills" ] = character->skills().toJson();
    characterJson[ "vitals" ] = character->vitals().toJson();
    characterJson[ "wallet" ] = character->wallet().toJson();
    _sender.send( sessionId, Message::MessageSenderType::CHARACTER_UPDATE, characterJson );
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
}

} // namespace Core::System
