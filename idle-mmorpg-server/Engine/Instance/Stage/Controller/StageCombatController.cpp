#include "StageCombatController.h"

namespace Engine {

StageCombatController::StageCombatController( Domain::Stage* stage ) :
    StageController( stage ) {
}

void StageCombatController::onCharacterEnter( CharacterInstance* characterInstance ) {
}

void StageCombatController::onCharacterExit( const std::string& sessionId ) {
}

void StageCombatController::onTick() {

    // for ( auto it = _combatInstances.begin(); it != _combatInstances.end(); ) {
    //     CombatInstance* combatInstance = it->get();
    //     combatInstance->process();

    //            // Engine::NotificationSystem::notifyCombat( combatInstance );

    //     if ( combatInstance->isFinished() ) {
    //         for ( const auto& [ sessionId, _ ] : combatInstance->characters() ) {
    //             _characterCombatCache.erase( sessionId );
    //         }

    //         it = _combatInstances.erase( it );

    //         for ( const auto& [ otherSessionId, otherChar ] : _characters ) {
    //             if ( _characterCombatCache.find( otherSessionId ) == _characterCombatCache.end() ) {
    //                 if ( _characterCombatCache.find( otherSessionId ) == _characterCombatCache.end() ) {
    //                     std::vector<CombatInstance*> allInstances;
    //                     // std::string otherStructure = otherChar->coordinates().structureId();

    //                            // for ( auto& ci : _combatInstances ) {
    //                            //     if ( ci->structureId() == otherStructure ) {
    //                            //         allInstances.push_back( ci.get() );
    //                            //     }
    //                            // }

    //                            // Engine::NotificationSystem::notifyCombatInstances( otherSessionId, allInstances );
    //                 }
    //             }
    //         }

    //     } else {
    //         ++it;
    //     }
    // }
}

// void StageInstance::createCombat( const std::string& sessionId, CharacterInstance* characterInstance ) {
//     if ( _characterCombatCache.find( sessionId ) != _characterCombatCache.end() ) {
//         return;
//     }

//     std::string roomId = drogon::utils::getUuid();

//     // auto combatInstance = std::make_unique<CombatInstance>( _stage, roomId, character->name() );
//     // CombatInstance* combatInstancePtr = combatInstance.get();

//     // combatInstancePtr->addCharacter( sessionId, character );
//     // _characterCombatCache[ sessionId ] = combatInstancePtr;
//     // _combatInstances.push_back( std::move( combatInstance ) );

//     for ( const auto& [ otherSessionId, otherChar ] : _characters ) {
//         // if ( _characterCombatCache.find( otherSessionId ) == _characterCombatCache.end() ) {
//         //     std::vector<CombatInstance*> allInstances;
//         //     std::string otherStructure = otherChar->coordinates().structureId();

//         //     for ( auto& ci : _combatInstances ) {
//         //         if ( ci->structureId() == otherStructure ) {
//         //             allInstances.push_back( ci.get() );
//         //         }
//         //     }

//         //     // Engine::NotificationSystem::notifyCombatInstances( otherSessionId, allInstances );
//         // }
//     }
// }

// void StageInstance::enterCombat( const std::string& sessionId, CharacterInstance* characterInstance, const std::string& roomId ) {
//     if ( _characterCombatCache.find( sessionId ) != _characterCombatCache.end() ) {
//         return;
//     }

//     // for ( const auto& combatInstance : _combatInstances ) {
//     //     if ( combatInstance->id() == roomId ) {
//     //         combatInstance->addCharacter( sessionId, character );
//     //         _characterCombatCache[ sessionId ] = combatInstance.get();
//     //         return;
//     //     }
//     // }
// }

// void StageInstance::exitCombat( const std::string& sessionId ) {
//     auto it = _characterCombatCache.find( sessionId );
//     if ( it == _characterCombatCache.end() ) {
//         return;
//     }

//     CombatInstance* combatInstance = it->second;
//     combatInstance->removeCharacter( sessionId );
//     _characterCombatCache.erase( it );
// }

} // namespace Engine
