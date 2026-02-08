#include "WorldInstance.h"

#include <Repository/Character/CharacterRepository.h>

namespace Engine {

WorldInstance::WorldInstance( Domain::World* world ) :
    _mutex(),
    _world( world ),
    _stages(),
    _characters(),
    _characterToStage() {
}

bool WorldInstance::addCharacter( const std::string& sessionId, std::unique_ptr<Domain::Character> character ) {
    if ( !character ) {
        return false;
    }

    character->setSessionId( sessionId );

    Domain::CharacterStage& characterStage = character->stage();

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

    if ( stageInstance->addCharacter( sessionId, character.get() ) ) {
        _characters[ sessionId ] = std::move( character );
        _characterToStage[ sessionId ] = stageInstance.get();
        return true;
    }

    return false;
}

void WorldInstance::removeCharacter( const std::string& sessionId ) {
    std::lock_guard lock( _mutex );

    // auto itLoc = _characterToLocation.find( sessionId );
    // if ( itLoc != _characterToLocation.end() ) {
    //     LocationInstance* locInstance = itLoc->second;
    //     if ( locInstance ) {
    //         locInstance->removeCharacter( sessionId );
    //     }
    //     _characterToLocation.erase( itLoc );
    // }

    // auto itChar = _characters.find( sessionId );
    // if ( itChar != _characters.end() ) {
    //     Repository::CharacterRepository().updateCharacter( *itChar->second );
    //     _characters.erase( itChar );
    // }

    // TODO: apagar LocationInstance se vazio
}

void WorldInstance::moveCharacter( const std::string& sessionId, const std::string& destination ) {
    std::lock_guard lock( _mutex );

    auto charIt = _characters.find( sessionId );
    if ( charIt == _characters.end() ) {
        return;
    }

    // Domain::Character* character = charIt->second.get();

    auto locIt = _characterToStage.find( sessionId );
    if ( locIt == _characterToStage.end() ) {
        return;
    }

    // StageInstance* currentInstance = locIt->second;
    // Domain::Stage* currentStage = currentInstance->stage();

    removeCharacter( sessionId );

    // Update Stage

    addCharacter( sessionId, std::move( _characters[ sessionId ] ) );
}

StageInstance* WorldInstance::characterStageInstance( const std::string& sessionId ) {
    std::lock_guard lock( _mutex );
    auto it = _characterToStage.find( sessionId );
    if ( it != _characterToStage.end() ) {
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
