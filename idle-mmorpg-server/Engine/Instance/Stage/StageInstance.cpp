#include "StageInstance.h"

#include <iostream>

#include <drogon/drogon.h>

#include <Engine/Manager/Action/ActionManager.h>
#include <Shared/Commons/Singleton.h>

namespace Engine {

StageInstance::StageInstance( Domain::Stage* stage ) :
    _stage( stage ),
    _characters( {} ),
    _controllers( {} ) {

    // --- Combat ---
    _combatController = std::make_unique<StageCombatController>( stage );
    _controllers.push_back( _combatController.get() );
}

bool StageInstance::addCharacter( const std::string& sessionId, CharacterInstance* characterInstance ) {
    std::lock_guard lock( _mutex );
    _characters[ sessionId ] = characterInstance;

    std::cout << "StageInstance::addCharacter"
              << " [Character] " << characterInstance->character().name()
              << " [Entering] " << _stage->level()
              << " [SessionID] " << sessionId << std::endl;

    characterInstance->sendMessage( MessageSenderType::STAGE, _stage->toJson() );

    for ( auto* controller : _controllers ) {
        controller->onCharacterEnter( characterInstance );
    }

    return true;
}

void StageInstance::removeCharacter( const std::string& sessionId ) {
    std::lock_guard lock( _mutex );
    std::cout << "StageInstance::removeCharacter" << " [SessionID] " << sessionId << std::endl;

    for ( auto* controller : _controllers ) {
        controller->onCharacterExit( sessionId );
    }

    _characters.erase( sessionId );
}

void StageInstance::tick() {
    std::lock_guard lock( _mutex );

    for ( const auto& [ sessionId, character ] : _characters ) {
        character->onTick();
    }

    for ( auto* controller : _controllers ) {
        controller->onTick();
    }
}

void StageInstance::handleMessage( CharacterInstance* character, MessageReceiverType type, const Json::Value& payload ) {
    std::lock_guard lock( _mutex );
    switch ( type ) {

    case MessageReceiverType::COMBAT_ROOM_CREATE:
    case MessageReceiverType::COMBAT_ROOM_ENTER:
    case MessageReceiverType::COMBAT_ROOM_EXIT:
        _combatController->handleMessage( character, type, payload );
        break;

    default:
        break;
    }
}

} // namespace Engine
