#include "WorldManager.h"

#include <chrono>

#include <Domain/Character/Character.h>
#include <Engine/Instance/Character/CharacterInstance.h>
#include <Manager/Server/ServerConfigurationManager.h>
#include <Repository/Character/CharacterRepository.h>
#include <Shared/Commons/Singleton.h>

#include "WorldFactory.h"

namespace Manager {

WorldManager::WorldManager() :
    _running( false ),
    _thread(),
    _world( nullptr ),
    _worldInstance( nullptr ) {}

WorldManager::~WorldManager() {}

Engine::WorldInstance* WorldManager::worldInstance() {
    return _worldInstance.get();
}

void WorldManager::initialize( const std::string& mapPath ) {
    if ( !_world ) {
        _world = Manager::WorldFactory::createWorld( mapPath );
    }

    if ( !_worldInstance ) {
        _worldInstance.reset( new Engine::WorldInstance( _world.get() ) );
    }

    if ( _running ) {
        return;
    }

    const int tick = Commons::Singleton<Manager::ServerConfigurationManager>::instance().tickRate();
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

    std::unique_ptr<Engine::CharacterInstance> characterInstance = std::make_unique<Engine::CharacterInstance>( std::move( character ) );

    return _worldInstance->addCharacter( sessionId, std::move( characterInstance ) );
}

void WorldManager::removeCharacter( const std::string& sessionId ) {
    _worldInstance->removeCharacter( sessionId );
}

} // namespace Manager
