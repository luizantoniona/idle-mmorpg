#include "RegionInstance.h"

#include <Model/Character/CharacterCoordinates.h>
#include <Model/World/Location/Location.h>

namespace Core::Instance {

RegionInstance::RegionInstance( Model::Region* region ) :
    _mutex(),
    _sender(),
    _characters( {} ),
    _region( region ) {}

bool RegionInstance::addCharacter( const std::string& sessionId, Model::Character* character ) {
    if ( !character ) {
        return false;
    }

    const Model::CharacterCoordinates coordinates = character->coordinates();

    Model::Location* locationModel = _region->locationByCoordinates( coordinates.x(), coordinates.y(), coordinates.z() );
    if ( !locationModel ) {
        return false;
    }

    const std::string locationId = locationModel->id();

    std::lock_guard lock( _mutex );

    auto& locationInstance = _locations[locationId];
    if ( !locationInstance ) {
        locationInstance = std::make_unique<LocationInstance>( locationModel );
    }

    if ( locationInstance->addCharacter( sessionId, character ) ) {
        _characters[sessionId] = character;
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
}

void RegionInstance::moveCharacter( const std::string& sessionId ) {
    std::lock_guard lock( _mutex );
    // TODO: Ver lógica para mover no locationInstance
    // TODO: Lembrar de ajustar cache
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

} // namespace Core::Instance
