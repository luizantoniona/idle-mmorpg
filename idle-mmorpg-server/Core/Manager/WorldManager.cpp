#include "WorldManager.h"

#include <chrono>

#include <Core/Factory/World/WorldFactory.h>
#include <Model/Character/Character.h>
#include <Repository/Character/CharacterRepository.h>

namespace Core::Manager {

WorldManager::WorldManager() :
    _running( false ),
    _thread(),
    _world( nullptr ),
    _worldInstance( nullptr ) {}

WorldManager::~WorldManager() {}

Instance::WorldInstance* WorldManager::worldInstance() {
    return _worldInstance.get();
}

void WorldManager::initialize( const std::string& mapPath ) {
    if ( !_world ) {
        _world = Core::Factory::WorldFactory::createWorld( mapPath );
    }

    if ( !_worldInstance ) {
        _worldInstance.reset( new Core::Instance::WorldInstance( _world.get() ) );
    }

    start();
}

void WorldManager::start() {
    if ( _running ) {
        return;
    }

    _running = true;
    _thread = std::thread( [ this ]() {
            using clock = std::chrono::steady_clock;
            auto nextTick = clock::now();

            while ( _running ) {
                nextTick += std::chrono::milliseconds( 50 );

                _worldInstance->tick();

                std::this_thread::sleep_until( nextTick );
            }
        } );
}

void WorldManager::stop() {
    _running = false;

    if ( _thread.joinable() ) {
        _thread.join();
    }
}

bool WorldManager::addCharacter( const std::string& uuid, int idUser, int idCharacter ) {
    auto character = Repository::CharacterRepository().findByIdUserAndIdCharacter( idUser, idCharacter );

    if ( !character ) {
        return false;
    }

    if ( _worldInstance->hasCharacter( idCharacter ) ) {
        return false;
    }

    return _worldInstance->addCharacter( uuid, std::move( character ) );
}

void WorldManager::removeCharacter( const std::string& uuid ) {
    _worldInstance->removeCharacter( uuid );
}

} // namespace Core::Manager
