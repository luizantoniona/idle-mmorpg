#include "WorldInstance.h"

#include <Domain/Character/CharacterCoordinates.h>

namespace Engine {

bool WorldInstance::addCharacter( const std::string& sessionId, std::unique_ptr<Domain::Character> character ) {
    if ( !character ) {
        return false;
    }

    character->setSessionId( sessionId );
    Domain::CharacterCoordinates& coordinates = character->coordinates();

    Domain::Location* location = _world->locationById( coordinates.locationId() );
    if ( !location ) {
        if ( _world->locations().empty() ) {
            return false;
        }

        location = _world->locations().front().get();
        coordinates.setLocationId( location->id() );
        coordinates.setStructureId( "" );
    }

    std::lock_guard lock( _mutex );

    auto& locInstance = _locations[ location->id() ];
    if ( !locInstance ) {
        locInstance = std::make_unique<LocationInstance>( location );
    }

    if ( locInstance->addCharacter( sessionId, character.get() ) ) {
        _characters[ sessionId ] = std::move( character );
        _characterToLocation[ sessionId ] = locInstance.get();
        return true;
    }

    return false;
}

void WorldInstance::removeCharacter( const std::string& sessionId ) {
    std::lock_guard lock( _mutex );

    auto itLoc = _characterToLocation.find( sessionId );
    if ( itLoc != _characterToLocation.end() ) {
        LocationInstance* locInstance = itLoc->second;
        if ( locInstance ) {
            locInstance->removeCharacter( sessionId );
        }
        _characterToLocation.erase( itLoc );
    }

    auto itChar = _characters.find( sessionId );
    if ( itChar != _characters.end() ) {
        Repository::CharacterRepository().updateCharacter( *itChar->second );
        _characters.erase( itChar );
    }

    // TODO: apagar LocationInstance se vazio
}

void WorldInstance::moveCharacter( const std::string& sessionId, const std::string& destination ) {
    std::lock_guard lock( _mutex );

    auto charIt = _characters.find( sessionId );
    if ( charIt == _characters.end() ) {
        return;
    }

    Domain::Character* character = charIt->second.get();

    auto locIt = _characterToLocation.find( sessionId );
    if ( locIt == _characterToLocation.end() ) {
        return;
    }

    LocationInstance* currentInstance = locIt->second;
    Domain::Location* currentLocation = currentInstance->location();

    bool validConnection = false;
    for ( const auto& connection : currentLocation->connections() ) {
        if ( connection.destination() == destination ) {
            validConnection = true;
            break;
        }
    }
    if ( !validConnection ) {
        return;
    }

    Domain::Location* destinationLocation = _world->locationById( destination );
    if ( !destinationLocation ) {
        return;
    }

    removeCharacter( sessionId );

    character->coordinates().setLocationId( destinationLocation->id() );
    character->coordinates().setStructureId( "" );
    character->action().clear();

    addCharacter( sessionId, std::move( _characters[ sessionId ] ) );
}

LocationInstance* WorldInstance::characterLocationInstance( const std::string& sessionId ) {
    std::lock_guard lock( _mutex );
    auto it = _characterToLocation.find( sessionId );
    if ( it != _characterToLocation.end() ) {
        return it->second;
    }
    return nullptr;
}

bool WorldInstance::hasCharacter( int idCharacter ) {
    std::lock_guard lock( _mutex );
    for ( const auto& [ sid, character ] : _characters ) {
        if ( character && character->idCharacter() == idCharacter ) {
            return true;
        }
    }
    return false;
}

void WorldInstance::tick() {
    std::lock_guard lock( _mutex );
    for ( auto& [ _, location ] : _locations ) {
        location->tick();
    }
}

void WorldInstance::handleCharacterMessage( const std::string& sessionId, Message::MessageReceiverType type, const Json::Value& payload ) {
    if ( type == Message::MessageReceiverType::CHARACTER_LOCATION_UPDATE ) {
        std::string destination = payload[ "destination" ].asString();
        moveCharacter( sessionId, destination );
    }
}

} // namespace Engine
