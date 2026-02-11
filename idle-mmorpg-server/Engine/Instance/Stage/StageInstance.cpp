#include "StageInstance.h"

#include <iostream>

#include <drogon/drogon.h>

namespace Engine {

StageInstance::StageInstance( Domain::Stage* stage ) :
    _stage( stage ),
    _characters( {} ),
    _characterCombatCache( {} ),
    _combatInstances() {
}

bool StageInstance::addCharacter( const std::string& sessionId, CharacterInstance* characterInstance ) {
    std::lock_guard lock( _mutex );
    _characters[ sessionId ] = characterInstance;

    std::cout << "StageInstance::addCharacter"
              << " [Character] " << characterInstance->character().name()
              << " [Entering] " << _stage->name()
              << " [SessionID] " << sessionId << std::endl;

    return true;
}

void StageInstance::removeCharacter( const std::string& sessionId ) {
    std::lock_guard lock( _mutex );
    std::cout << "StageInstance::removeCharacter" << " [SessionID] " << sessionId << std::endl;
    // exitCombat( sessionId );
    _characters.erase( sessionId );
}

void StageInstance::createCombat( const std::string& sessionId, CharacterInstance* characterInstance ) {
    if ( _characterCombatCache.find( sessionId ) != _characterCombatCache.end() ) {
        return;
    }

    std::string roomId = drogon::utils::getUuid();

    // auto combatInstance = std::make_unique<CombatInstance>( _stage, roomId, character->name() );
    // CombatInstance* combatInstancePtr = combatInstance.get();

    // combatInstancePtr->addCharacter( sessionId, character );
    // _characterCombatCache[ sessionId ] = combatInstancePtr;
    // _combatInstances.push_back( std::move( combatInstance ) );

    for ( const auto& [ otherSessionId, otherChar ] : _characters ) {
        // if ( _characterCombatCache.find( otherSessionId ) == _characterCombatCache.end() ) {
        //     std::vector<CombatInstance*> allInstances;
        //     std::string otherStructure = otherChar->coordinates().structureId();

        //     for ( auto& ci : _combatInstances ) {
        //         if ( ci->structureId() == otherStructure ) {
        //             allInstances.push_back( ci.get() );
        //         }
        //     }

        //     // Engine::NotificationSystem::notifyCombatInstances( otherSessionId, allInstances );
        // }
    }
}

void StageInstance::enterCombat( const std::string& sessionId, CharacterInstance* characterInstance, const std::string& roomId ) {
    if ( _characterCombatCache.find( sessionId ) != _characterCombatCache.end() ) {
        return;
    }

    // for ( const auto& combatInstance : _combatInstances ) {
    //     if ( combatInstance->id() == roomId ) {
    //         combatInstance->addCharacter( sessionId, character );
    //         _characterCombatCache[ sessionId ] = combatInstance.get();
    //         return;
    //     }
    // }
}

void StageInstance::exitCombat( const std::string& sessionId ) {
    auto it = _characterCombatCache.find( sessionId );
    if ( it == _characterCombatCache.end() ) {
        return;
    }

    CombatInstance* combatInstance = it->second;
    combatInstance->removeCharacter( sessionId );
    _characterCombatCache.erase( it );
}

void StageInstance::tick() {
    std::lock_guard lock( _mutex );

    for ( const auto& [ sessionId, character ] : _characters ) {

        // Engine::RegenerationSystem::processSpellsCooldown( sessionId, character );
        // Engine::EffectSystem::processEffects( sessionId, character );

        // if ( character->action().id() == "combat" ) {
        //     continue;
        // }

        // Engine::RegenerationSystem::processRegeneration( sessionId, character );

        // if ( character->action().id() == "idle" ) {
        //     continue;
        // }

        // if ( character->action().id() == "train" ) {
        //     _trainingSystem.process( sessionId, character );
        //     continue;
        // }

        // _actionSystem.process( sessionId, character );
    }

    for ( auto it = _combatInstances.begin(); it != _combatInstances.end(); ) {
        CombatInstance* combatInstance = it->get();
        combatInstance->process();

        // Engine::NotificationSystem::notifyCombat( combatInstance );

        if ( combatInstance->isFinished() ) {
            for ( const auto& [ sessionId, _ ] : combatInstance->characters() ) {
                _characterCombatCache.erase( sessionId );
            }

            it = _combatInstances.erase( it );

            for ( const auto& [ otherSessionId, otherChar ] : _characters ) {
                if ( _characterCombatCache.find( otherSessionId ) == _characterCombatCache.end() ) {
                    if ( _characterCombatCache.find( otherSessionId ) == _characterCombatCache.end() ) {
                        std::vector<CombatInstance*> allInstances;
                        // std::string otherStructure = otherChar->coordinates().structureId();

                        // for ( auto& ci : _combatInstances ) {
                        //     if ( ci->structureId() == otherStructure ) {
                        //         allInstances.push_back( ci.get() );
                        //     }
                        // }

                        // Engine::NotificationSystem::notifyCombatInstances( otherSessionId, allInstances );
                    }
                }
            }

        } else {
            ++it;
        }
    }
}

void StageInstance::handleCharacterMessage( const std::string& sessionId, MessageReceiverType type, const Json::Value& payload ) {
    std::lock_guard lock( _mutex );

    auto it = _characters.find( sessionId );
    if ( it == _characters.end() ) {
        return;
    }
    CharacterInstance* character = it->second;

    CombatInstance* combat = nullptr;
    auto itCombat = _characterCombatCache.find( sessionId );
    if ( itCombat != _characterCombatCache.end() ) {
        combat = itCombat->second;
    }

    switch ( type ) {
    case MessageReceiverType::CHARACTER_ACTION_UPDATE: {
        // TODO
        break;
    }

    case MessageReceiverType::CHARACTER_EQUIP_ITEM:
        // Engine::ItemSystem::characterEquipItem( sessionId, character, payload );
        break;
    case MessageReceiverType::CHARACTER_USE_ITEM:
        // Engine::ItemSystem::characterUseItem( sessionId, character, payload );
        break;
    case MessageReceiverType::CHARACTER_CAST_SPELL: {
        std::string spellType = payload[ "type" ].asString();
        std::string spellId = payload[ "id" ].asString();

        if ( spellType == "healing" ) {
            // Engine::RegenerationSystem::castHealingSpell( sessionId, character, spellId );

        } else if ( spellType == "attack" && combat ) {
            // combat->handleCharacterAttackSpell( sessionId, character, spellId );
        }

        break;
    }

    case MessageReceiverType::COMBAT_ROOM_CREATE:
        createCombat( sessionId, character );
        break;
    case MessageReceiverType::COMBAT_ROOM_ENTER: {
        std::string roomId = payload[ "id" ].asString();
        enterCombat( sessionId, character, roomId );
        break;
    }
    case MessageReceiverType::COMBAT_ROOM_EXIT:
        exitCombat( sessionId );
        break;
    default:
        break;
    }
}

} // namespace Engine
