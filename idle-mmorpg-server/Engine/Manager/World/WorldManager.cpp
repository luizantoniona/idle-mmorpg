#include "WorldManager.h"

#include <chrono>

#include <Domain/Character/Character.h>
#include <Engine/Repository/Character/CharacterRepository.h>
#include <Engine/Manager/Configuration/ServerConfigurationManager.h>
#include <Shared/Commons/Singleton.h>

#include "WorldFactory.h"

namespace Engine {

WorldManager::WorldManager() :
    _running( false ),
    _thread(),
    _world( nullptr ),
    _worldInstance( nullptr ) {}

WorldManager::~WorldManager() {}

WorldInstance* WorldManager::worldInstance() {
    return _worldInstance.get();
}

void WorldManager::initialize( const std::string& mapPath ) {
    if ( !_world ) {
        _world = Engine::WorldFactory::createWorld( mapPath );
    }

    if ( !_worldInstance ) {
        _worldInstance.reset( new Engine::WorldInstance( _world.get() ) );
    }

    start();
}

void WorldManager::start() {
    if ( _running ) {
        return;
    }

    // TODO: Make the localInstance running on a threadPool

    const int tick = Commons::Singleton<Engine::ServerConfigurationManager>::instance().tickRate();
    const int msPerTick = 1000 / tick;

    _running = true;
    _thread = std::thread( [ this, msPerTick ]() {
            using clock = std::chrono::steady_clock;
            auto nextTick = clock::now();

            while ( _running ) {
                nextTick += std::chrono::milliseconds( msPerTick );

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

bool WorldManager::addCharacter( const std::string& sessionId, int idUser, int idCharacter ) {
    auto character = Repository::CharacterRepository().findByIdUserAndIdCharacter( idUser, idCharacter );

    if ( !character ) {
        return false;
    }

    if ( _worldInstance->hasCharacter( idCharacter ) ) {
        return false;
    }

    return _worldInstance->addCharacter( sessionId, std::move( character ) );
}

void WorldManager::removeCharacter( const std::string& uuid ) {
    _worldInstance->removeCharacter( uuid );
}

} // namespace Engine
