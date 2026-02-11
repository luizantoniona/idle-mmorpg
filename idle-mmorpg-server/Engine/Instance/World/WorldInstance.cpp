#include "WorldInstance.h"

namespace Engine {

WorldInstance::WorldInstance( Domain::World* world ) :
    _mutex(),
    _world( world ),
    _characters(),
    _stages(),
    _characterToStage() {
}

bool WorldInstance::hasCharacter( int idCharacter ) {
    std::lock_guard lock( _mutex );
    for ( const auto& [ sid, characterInstance ] : _characters ) {
        if ( characterInstance && characterInstance->character().idCharacter() == idCharacter ) {
            return true;
        }
    }
    return false;
}

bool WorldInstance::addCharacter( const std::string& sessionId, std::unique_ptr<CharacterInstance> characterInstance ) {
    if ( !characterInstance ) {
        return false;
    }

    characterInstance->setSessionId( sessionId );

    Domain::Character& character = characterInstance->character();
    Domain::CharacterStage& characterStage = character.stage();

    Domain::Stage* stage = _world->stageById( characterStage.idStage() );

    if ( !stage ) {
        if ( _world->stages().empty() ) {
            return false;
        }

        stage = _world->stages().front().get();
        characterStage.setIdStage( stage->id() );
    }

    std::lock_guard lock( _mutex );

    auto& stageInstance = _stages[ stage->id() ];
    if ( !stageInstance ) {
        stageInstance = std::make_unique<StageInstance>( stage );
    }

    if ( stageInstance->addCharacter( sessionId, characterInstance.get() ) ) {
        _characters[ sessionId ] = std::move( characterInstance );
        _characterToStage[ sessionId ] = stageInstance.get();

        _characters[ sessionId ]->onEnterWorld();

        return true;
    }

    return false;
}

void WorldInstance::removeCharacter( const std::string& sessionId ) {
    std::lock_guard lock( _mutex );

    auto stageIterator = _characterToStage.find( sessionId );

    if ( stageIterator != _characterToStage.end() ) {
        StageInstance* stageInstance = stageIterator->second;

        if ( stageInstance ) {
            stageInstance->removeCharacter( sessionId );
        }

        _characterToStage.erase( stageIterator );
    }

    auto characterIterator = _characters.find( sessionId );

    if ( characterIterator != _characters.end() ) {

        characterIterator->second->onLeaveWorld();

        _characters.erase( characterIterator );
    }
}

StageInstance* WorldInstance::characterStageInstance( const std::string& sessionId ) {
    std::lock_guard lock( _mutex );
    auto it = _characterToStage.find( sessionId );
    if ( it != _characterToStage.end() ) {
        return it->second;
    }
    return nullptr;
}

void WorldInstance::tick() {
    std::lock_guard lock( _mutex );
    for ( auto& [ _, stage ] : _stages ) {
        stage->tick();
    }
}

void WorldInstance::handleCharacterMessage( const std::string& sessionId, Engine::MessageReceiverType type, const Json::Value& payload ) {
    switch ( type ) {
    case Engine::MessageReceiverType::UNKNOWN:
        break;
    default:
        break;
    }
}

} // namespace Engine
