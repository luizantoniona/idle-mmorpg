#include "LocationInstance.h"

#include <iostream>

#include <Core/Message/MessageSenderType.h>
#include <Core/System/ActionSystem.h>

namespace Core::Instance {

LocationInstance::LocationInstance( Model::Location* location ) :
    _mutex(),
    _location( location ),
    _characters( {} ),
    _sender(),
    _actionSystem( location ) {}

void LocationInstance::notifyCharacter( const std::string& sessionId, Model::Character* character ) {
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

void LocationInstance::notifyLocation( const std::string& sessionId ) {
    Json::Value payloadLocation;
    payloadLocation[ "location" ] = _location->toJson();
    _sender.send( sessionId, Message::MessageSenderType::LOCATION_UPDATE_POSITION, payloadLocation );
}

bool LocationInstance::addCharacter( const std::string& sessionId, Model::Character* character ) {
    std::lock_guard lock( _mutex );
    _characters[sessionId] = character;

    std::cout << "LocationInstance::addCharacter"
              << " [Character] " << character->name()
              << " [Entering] " << _location->name()
              << " [SessionID] " << sessionId << std::endl;

    notifyCharacter( sessionId, character );
    notifyLocation( sessionId );
    _actionSystem.notifyCharacterActions( sessionId, character );

    return true;
}

void LocationInstance::removeCharacter( const std::string& sessionId ) {
    std::lock_guard lock( _mutex );
    std::cout << "LocationInstance::removeCharacter" << " [SessionID] " << sessionId << std::endl;
    _characters.erase( sessionId );
}

void LocationInstance::tick() {
    std::lock_guard lock( _mutex );

    for ( const auto& [ sessionId, character ] : _characters ) {
        _actionSystem.process( sessionId, character );
    }
}

void LocationInstance::handleCharacterMessage( const std::string& sessionId, Message::MessageReceiverType type, const Json::Value& payload ) {
    std::lock_guard lock( _mutex );

    auto it = _characters.find( sessionId );
    if ( it == _characters.end() ) {
        return;
    }

    Model::Character* character = it->second;

    switch ( type ) {
        case Message::MessageReceiverType::CHARACTER_UPDATE_ACTION:
            _actionSystem.changeAction( sessionId, character, payload );
            break;
        default:
            break;
    }
}

} // namespace Core::Instance
