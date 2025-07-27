#include "LocationInstance.h"

#include <iostream>

#include <Core/Message/MessageType.h>

using System::Message::MessageType;

namespace Core::Instance {

LocationInstance::LocationInstance( Model::Location* location ) :
    _mutex(),
    _sender(),
    _characters( {} ),
    _location( location ) {}

bool LocationInstance::addCharacter( const std::string& sessionId, Model::Character* character ) {
    std::lock_guard lock( _mutex );
    _characters[sessionId] = character;

    std::cout << "LocationInstance::addCharacter"
              << " [Character] " << character->dsName()
              << " [Entering] " << _location->name()
              << " [SessionID] " << sessionId << std::endl;

    Json::Value payloadLocation;
    payloadLocation[ "location" ] = _location->toJson();
    _sender.send( sessionId, MessageType::LOCATION_UPDATE_POSITION, payloadLocation );

    Json::Value payloadLocationActions;
    // for ()
    // payloadLocationActions[ "actions" ] = _location->actions();
    _sender.send( sessionId, MessageType::LOCATION_UPDATE_ACTIONS, payloadLocationActions );

    return true;
}

void LocationInstance::removeCharacter( const std::string& sessionId ) {
    std::lock_guard lock( _mutex );
    _characters.erase( sessionId );
}

void LocationInstance::tick() {
    std::lock_guard lock( _mutex );

    for ( const auto& [ sessionId, character ] : _characters ) {}

    // TODO: lógica de simulação futura (spawn, eventos, efeitos)
}

} // namespace Core::Instance
