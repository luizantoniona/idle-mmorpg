#include "StageCombatController.h"

namespace Engine {

StageCombatController::StageCombatController( Domain::Stage* stage ) :
    StageController( stage ),
    _combats(),
    _characters(),
    _characterToCombatCache() {
}

void StageCombatController::onCharacterEnter( CharacterInstance* characterInstance ) {
    const std::string sessionId = characterInstance->sessionId();
    _characters[ sessionId ] = characterInstance;

    notifyCombatRooms();
}

void StageCombatController::onCharacterExit( const std::string& sessionId ) {
    auto it = _characterToCombatCache.find( sessionId );
    if ( it != _characterToCombatCache.end() ) {

        CombatInstance* combat = it->second;
        combat->removeCharacter( sessionId );
        _characterToCombatCache.erase( it );

        if ( combat->characters().empty() ) {
            _combats.erase( combat->id() );
        }

        notifyCombatRooms();
    }

    _characters.erase( sessionId );
}

void StageCombatController::onTick() {
    for ( auto it = _combats.begin(); it != _combats.end(); ) {
        CombatInstance* combat = it->second.get();
        combat->tick();

        if ( combat->isFinished() ) {

            for ( const auto& [ sessionId, _ ] : combat->characters() ) {
                _characterToCombatCache.erase( sessionId );
            }

            it = _combats.erase( it );

            notifyCombatRooms();

        } else {
            ++it;
        }
    }
}

void StageCombatController::handleMessage( CharacterInstance* characterInstance, MessageReceiverType type, const Json::Value& payload ) {
    switch ( type ) {
    case MessageReceiverType::COMBAT_ROOM_CREATE:
        createCombat( characterInstance );
        break;
    case MessageReceiverType::COMBAT_ROOM_ENTER:
        if ( payload.isMember( "roomId" ) ) {
            enterCombat( characterInstance, payload[ "roomId" ].asString() );
        }
        break;
    case MessageReceiverType::COMBAT_ROOM_EXIT:
        exitCombat( characterInstance );
        break;
    default:
        break;
    }
}

void StageCombatController::notifyCombatRooms() {
    Json::Value payload;
    Json::Value combatArray;

    for ( const auto& [ id, combat ] : _combats ) {
        combatArray.append( combat->instanceToJson() );
    }

    payload[ "combatInstances" ] = combatArray;

    for ( const auto& [ sessionId, character ] : _characters ) {
        if ( _characterToCombatCache.find( sessionId ) != _characterToCombatCache.end() ) {
            continue;
        }

        character->sendMessage( MessageSenderType::COMBAT_ROOMS, payload );
    }
}

void StageCombatController::createCombat( CharacterInstance* characterInstance ) {
    const std::string sessionId = characterInstance->sessionId();

    if ( _characterToCombatCache.find( sessionId ) != _characterToCombatCache.end() ) {
        return;
    }

    std::string roomId = drogon::utils::getUuid();

    auto combatInstance = std::make_unique<CombatInstance>( _stage, roomId, characterInstance->character().name() );
    CombatInstance* combatInstancePtr = combatInstance.get();

    combatInstancePtr->addCharacter( sessionId, characterInstance );
    _characterToCombatCache[ sessionId ] = combatInstancePtr;
    _combats.emplace( roomId, std::move( combatInstance ) );

    notifyCombatRooms();
}

void StageCombatController::enterCombat( CharacterInstance* characterInstance, const std::string& roomId ) {
    const std::string sessionId = characterInstance->sessionId();

    if ( _characterToCombatCache.find( sessionId ) != _characterToCombatCache.end() ) {
        return;
    }

    auto it = _combats.find( roomId );
    if ( it == _combats.end() ) {
        return;
    }

    CombatInstance* combat = it->second.get();
    combat->addCharacter( sessionId, characterInstance );
    _characterToCombatCache[ sessionId ] = combat;

    notifyCombatRooms();
}

void StageCombatController::exitCombat( CharacterInstance* characterInstance ) {
    const std::string sessionId = characterInstance->sessionId();

    auto it = _characterToCombatCache.find( sessionId );
    if ( it == _characterToCombatCache.end() ) {
        return;
    }

    CombatInstance* combat = it->second;
    combat->removeCharacter( sessionId );
    _characterToCombatCache.erase( it );

    if ( combat->characters().empty() ) {
        _combats.erase( combat->id() );
    }

    notifyCombatRooms();
}

} // namespace Engine
