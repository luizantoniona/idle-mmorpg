#include "WorldInstance.h"

#include <iostream>

#include <Engine/Message/MessageHelper.h>
#include <Engine/Message/MessageReceiverType.h>

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

    Domain::Stage* stage = _world->stageByLevel( characterStage.stageLevel() );

    if ( !stage ) {
        if ( _world->stages().empty() ) {
            return false;
        }

        stage = _world->stages().front().get();
        characterStage.setStageLevel( stage->level() );
    }

    std::lock_guard lock( _mutex );

    auto& stageInstance = _stages[ stage->level() ];
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

void WorldInstance::handleMessage( const std::string& sessionId, const Json::Value& messageJson ) {
    const MessageReceiverType type = MessageHelper::stringToType( messageJson[ "type" ].asString() );

    if ( type == MessageReceiverType::UNKNOWN ) {
        std::cout << "Unknow message: received from: " << sessionId << " json: " << messageJson << std::endl;
        return;
    }

    const Json::Value& payload = messageJson[ "payload" ];

    CharacterInstance* character = nullptr;
    StageInstance* stage = nullptr;

    {
        std::lock_guard<std::mutex> lock( _mutex );

        auto itChar = _characters.find( sessionId );
        if ( itChar != _characters.end() ) {
            character = itChar->second.get();
        }

        auto itStage = _characterToStage.find( sessionId );
        if ( itStage != _characterToStage.end() ) {
            stage = itStage->second;
        }
    }

    if ( !character || !stage ) {
        return;
    }

    switch ( type ) {

        // --- Stage ---
    case Engine::MessageReceiverType::COMBAT_ROOM_CREATE:
    case Engine::MessageReceiverType::COMBAT_ROOM_ENTER:
    case Engine::MessageReceiverType::COMBAT_ROOM_EXIT:
        stage->handleMessage( character, type, payload );
        break;

        // --- Character ---
    case Engine::MessageReceiverType::CHARACTER_ACTION_SET:
    case Engine::MessageReceiverType::CHARACTER_ITEM_EQUIP:
    case Engine::MessageReceiverType::CHARACTER_ITEM_USE:
        character->handleMessage( type, payload );
        break;

    case Engine::MessageReceiverType::CHARACTER_STAGE_NEXT:
        // TODO: See if we need to send to character or what
        // TODO: Validate if every objective is complete inside character (flag completed)
        // TODO: If OK, WorldInstance Should change StageInstance from character
        // TODO: If Stage Changed, we must update character and save on database
        break;

    default:
        break;
    }
}

} // namespace Engine
