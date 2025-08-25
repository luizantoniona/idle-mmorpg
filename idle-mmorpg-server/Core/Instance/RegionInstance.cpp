#include "RegionInstance.h"

#include <iostream>

#include <Model/Character/CharacterCoordinates.h>
#include <Model/World/Location/Location.h>

namespace Core::Instance {

RegionInstance::RegionInstance( Model::Region* region ) :
    _mutex(),
    _characters( {} ),
    _region( region ) {}

bool RegionInstance::addCharacter( const std::string& sessionId, Model::Character* character ) {
    if ( !character ) {
        return false;
    }

    const Model::CharacterCoordinates coordinates = character->coordinates();

    Model::Location* location = _region->locationByCoordinates( coordinates.x(), coordinates.y(), coordinates.z() );
    if ( !location ) {
        return false;
    }

    const std::string locationId = location->id();

    std::lock_guard lock( _mutex );

    auto& locationInstance = _locations[locationId];
    if ( !locationInstance ) {
        locationInstance = std::make_unique<LocationInstance>( location );
    }

    if ( locationInstance->addCharacter( sessionId, character ) ) {
        _characters[ sessionId ] = character;
        _characterToLocation[sessionId] = locationInstance.get();
        return true;
    }

    return false;
}

void RegionInstance::removeCharacter( const std::string& sessionId ) {
    std::lock_guard lock( _mutex );

    auto locationIt = _characterToLocation.find( sessionId );
    if ( locationIt != _characterToLocation.end() ) {
        LocationInstance* locationInstance = locationIt->second;
        if ( locationInstance ) {
            locationInstance->removeCharacter( sessionId );
        }

        _characterToLocation.erase( locationIt );
    }

    _characters.erase( sessionId );

    // TODO: If location instance empty, delete it;
}

void RegionInstance::moveCharacter( const std::string& sessionId, const std::string& destination ) {
    std::lock_guard lock( _mutex );

    auto charIt = _characters.find( sessionId );
    if ( charIt == _characters.end() ) {
        return;
    }

    Model::Character* character = charIt->second;

    auto locIt = _characterToLocation.find( sessionId );
    if ( locIt == _characterToLocation.end() ) {
        return;
    }

    Model::Location* currentlocation = locIt->second->location();

    bool validConnection = false;

    // TODO: Verificar structure

    for ( const auto& connection : currentlocation->connections() ) {
        if ( connection.destination() == destination ) {
            validConnection = true;
            break;
        }
    }

    if ( !validConnection ) {
        return;
    }

    Model::Location* destinationLocation = _region->locationById( destination );
    if ( !destinationLocation ) {
        return;
    }

    removeCharacter( sessionId );

    character->coordinates().setX( destinationLocation->x() );
    character->coordinates().setY( destinationLocation->y() );
    character->coordinates().setZ( destinationLocation->z() );
    character->coordinates().setCurrentStructure( "" );
    character->action().clear();

    addCharacter( sessionId, character );
}

LocationInstance* RegionInstance::characterLocationInstance( const std::string& sessionId ) {
    std::lock_guard lock( _mutex );

    auto it = _characterToLocation.find( sessionId );
    if ( it != _characterToLocation.end() ) {
        return it->second;
    }

    return nullptr;
}

void RegionInstance::tick() {
    std::lock_guard lock( _mutex );
    for ( auto& [_, location] : _locations ) {
        location->tick();
    }
}

void RegionInstance::handleCharacterMessage( const std::string& sessionId, Message::MessageReceiverType type, const Json::Value& payload ) {
    auto it = _characters.find( sessionId );
    if ( it == _characters.end() ) {
        return;
    }

    switch ( type ) {
        case Message::MessageReceiverType::CHARACTER_LOCATION_UPDATE: {
            std::string destination = payload[ "destination" ].asString();
            moveCharacter( sessionId, destination );
            break;
        }
        default:
            break;
    }
}

} // namespace Core::Instance
