#include "WorldInstance.h"

#include <Model/Character/CharacterCoordinates.h>
#include <Model/World/Region.h>
#include <Repository/Character/CharacterRepository.h>

namespace Core::Instance {

WorldInstance::WorldInstance( Model::World* world ) :
    _mutex(),
    _characters(),
    _world( world ) {}

bool WorldInstance::addCharacter( const std::string& sessionId, std::unique_ptr<Model::Character> character ) {
    if ( !character ) {
        return false;
    }

    const Model::CharacterCoordinates coordinates = character->coordinates();

    for ( auto& regionModel : _world->regions() ) {

        if ( regionModel.get()->hasLocationWithCoordinates( coordinates.x(), coordinates.y(), coordinates.z() ) ) {

            std::lock_guard lock( _mutex );

            auto& regionInstance = _regions[regionModel.get()->id()];

            if ( !regionInstance ) {
                regionInstance = std::make_unique<RegionInstance>( regionModel.get() );
            }

            if ( regionInstance->addCharacter( sessionId, character.get() ) ) {
                _characters[sessionId] = std::move( character );
                _characterToRegion[sessionId] = regionInstance.get();

                return true;
            }
        }
    }

    return false;
}

void WorldInstance::removeCharacter( const std::string& sessionId ) {
    std::lock_guard lock( _mutex );

    auto itRegion = _characterToRegion.find( sessionId );
    if ( itRegion != _characterToRegion.end() ) {

        RegionInstance* regionInstance = itRegion->second;
        if ( regionInstance ) {
            regionInstance->removeCharacter( sessionId );
        }

        _characterToRegion.erase( itRegion );
    }

    auto itCharacter = _characters.find( sessionId );
    if ( itCharacter != _characters.end() ) {
        Repository::CharacterRepository().updateCharacter( *itCharacter->second );
        _characters.erase( itCharacter );
    }

    // TODO: If region instance empty, delete it;
}

void WorldInstance::moveCharacter( const std::string& sessionId ) {
    std::lock_guard lock( _mutex );
    // TODO: How to move the character between RegionInstances
    // TODO: Remember to adjust cache.
}

bool WorldInstance::hasCharacter( const int idCharacter ) {
    std::lock_guard lock( _mutex );
    for ( const auto& [ sessionId, character ] : _characters ) {
        if ( character && character->idCharacter() == idCharacter ) {
            return true;
        }
    }

    return false;
}

RegionInstance* WorldInstance::characterRegionInstance( const std::string& sessionId ) {
    std::lock_guard lock( _mutex );

    auto it = _characterToRegion.find( sessionId );
    if ( it != _characterToRegion.end() ) {
        return it->second;
    }

    return nullptr;
}

LocationInstance* WorldInstance::characterLocationInstance( const std::string& sessionId ) {
    std::lock_guard lock( _mutex );

    auto it = _characterToRegion.find( sessionId );
    if ( it == _characterToRegion.end() ) {
        return nullptr;
    }

    RegionInstance* regionInstance = it->second;
    if ( !regionInstance ) {
        return nullptr;
    }

    return regionInstance->characterLocationInstance( sessionId );
}

void WorldInstance::tick() {
    std::lock_guard lock( _mutex );
    for ( auto& [_, region] : _regions ) {
        region->tick();
    }
}

} // namespace Core::Instance
