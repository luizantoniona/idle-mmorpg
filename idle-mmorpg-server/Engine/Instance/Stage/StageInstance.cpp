#include "StageInstance.h"

#include <iostream>

#include <drogon/drogon.h>

namespace Engine {

StageInstance::StageInstance( Domain::Stage* stage ) :
    _stage( stage ),
    _characters( {} ),
    _controllers( {} ) {

    // --- Action ---
    _actionController = std::make_unique<StageActionController>( stage );
    _controllers.push_back( _actionController.get() );

    // --- Combat ---
    _combatController = std::make_unique<StageCombatController>( stage );
    _controllers.push_back( _combatController.get() );
}

bool StageInstance::addCharacter( const std::string& sessionId, CharacterInstance* characterInstance ) {
    std::lock_guard lock( _mutex );
    _characters[ sessionId ] = characterInstance;

    std::cout << "StageInstance::addCharacter"
              << " [Character] " << characterInstance->character().name()
              << " [Entering] " << _stage->name()
              << " [SessionID] " << sessionId << std::endl;

    // --- Controllers: Add CharacterInstances on necessary controllers

    characterInstance->sendMessage( MessageSenderType::STAGE, _stage->toJson() );

    return true;
}

void StageInstance::removeCharacter( const std::string& sessionId ) {
    std::lock_guard lock( _mutex );
    std::cout << "StageInstance::removeCharacter" << " [SessionID] " << sessionId << std::endl;

    // --- Controllers: Remove CharacterInstances from necessary controllers

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

void StageInstance::handleMessage( const std::string& sessionId, MessageReceiverType type, const Json::Value& payload ) {
    // std::lock_guard lock( _mutex );
    switch ( type ) {
        case MessageReceiverType::UNKNOWN:
            break;
        default:
            break;
    }
}

} // namespace Engine
