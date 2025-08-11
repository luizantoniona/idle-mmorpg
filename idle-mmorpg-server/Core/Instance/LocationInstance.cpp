#include "LocationInstance.h"

#include <iostream>

#include <drogon/drogon.h>

#include <Core/Message/MessageSenderType.h>
#include <Core/System/ActionSystem.h>
#include <Core/System/NotificationSystem.h>

namespace Core::Instance {

LocationInstance::LocationInstance( Model::Location* location ) :
    _mutex(),
    _location( location ),
    _characters( {} ),
    _actionSystem( location ),
    _trainingSystem( location ),
    _combatInstances(),
    _characterCombatCache() {}

bool LocationInstance::addCharacter( const std::string& sessionId, Model::Character* character ) {
    std::lock_guard lock( _mutex );
    _characters[sessionId] = character;

    std::cout << "LocationInstance::addCharacter"
              << " [Character] " << character->name()
              << " [Entering] " << _location->name()
              << " [SessionID] " << sessionId << std::endl;

    Core::System::NotificationSystem::notifyFullCharacter( sessionId, character );
    Core::System::NotificationSystem::notifyFullLocation( sessionId, _location );
    Core::System::NotificationSystem::notifyLocationActions( sessionId, character, _location );

    return true;
}

void LocationInstance::removeCharacter( const std::string& sessionId ) {
    std::lock_guard lock( _mutex );
    std::cout << "LocationInstance::removeCharacter" << " [SessionID] " << sessionId << std::endl;
    _characters.erase( sessionId );
}

void LocationInstance::createCombat( const std::string& sessionId, Model::Character* character ) {
    if ( _characterCombatCache.find( sessionId ) != _characterCombatCache.end() ) {
        return;
    }

    std::string roomId = drogon::utils::getUuid();

    auto combatInstance = std::make_unique<CombatInstance>( _location, roomId, character->name(), character->coordinates().currentStructure() );
    CombatInstance* combatInstancePtr = combatInstance.get();

    combatInstancePtr->addCharacter( sessionId, character );
    _characterCombatCache[sessionId] = combatInstancePtr;
    _combatInstances.push_back( std::move( combatInstance ) );
}

void LocationInstance::enterCombat( const std::string& sessionId, Model::Character* character, const std::string& roomId ) {
    if ( _characterCombatCache.find( sessionId ) != _characterCombatCache.end() ) {
        return;
    }

    for ( const auto& combatInstance : _combatInstances ) {
        if ( combatInstance->id() == roomId ) {
            combatInstance->addCharacter( sessionId, character );
            _characterCombatCache[sessionId] = combatInstance.get();
            return;
        }
    }
}

void LocationInstance::exitCombat( const std::string& sessionId ) {
    auto it = _characterCombatCache.find( sessionId );
    if ( it == _characterCombatCache.end() ) {
        return;
    }

    CombatInstance* combatInstance = it->second;
    combatInstance->removeCharacter( sessionId );
    _characterCombatCache.erase( it );
}

void LocationInstance::tick() {
    std::lock_guard lock( _mutex );

    for ( const auto& [ sessionId, character ] : _characters ) {
        if ( character->action().id() == "idle" ) {
            continue;
        }

        if ( character->action().id() == "train" ) {
            _trainingSystem.process( sessionId, character );
            continue;
        }

        if ( character->action().id() == "combat" ) {
            if ( _characterCombatCache.find( sessionId ) == _characterCombatCache.end() ) {
                std::vector<CombatInstance*> instancesToNotify = {};
                const std::string& characterStructureId = character->coordinates().currentStructure();

                for ( const auto& combatInstance : _combatInstances ) {
                    if ( combatInstance->structureId() == characterStructureId ) {
                        instancesToNotify.push_back( combatInstance.get() );
                    }
                }

                Core::System::NotificationSystem::notifyCombatInstances( sessionId, instancesToNotify );
            }
            continue;
        }

        _actionSystem.process( sessionId, character );
    }

    for ( auto it = _combatInstances.begin(); it != _combatInstances.end(); ) {
        CombatInstance* combatInstance = it->get();
        combatInstance->process();

        for ( const auto& [ sessionId, character ] : combatInstance->characters() ) {
            Core::System::NotificationSystem::notifyFullCharacter( sessionId, character );
        }

        Core::System::NotificationSystem::notifyCombat( combatInstance );

        if ( combatInstance->isFinished() ) {
            for ( const auto& [ sessionId, _ ] : combatInstance->characters() ) {
                _characterCombatCache.erase( sessionId );
            }

            it = _combatInstances.erase( it );
        } else {
            ++it;
        }
    }
}

void LocationInstance::handleCharacterMessage( const std::string& sessionId, Message::MessageReceiverType type, const Json::Value& payload ) {
    std::lock_guard lock( _mutex );

    auto it = _characters.find( sessionId );
    if ( it == _characters.end() ) {
        return;
    }

    Model::Character* character = it->second;

    switch ( type ) {
        case Message::MessageReceiverType::CHARACTER_STRUCTURE_UPDATE:
            _actionSystem.changeStructure( sessionId, character, payload );
            break;
        case Message::MessageReceiverType::CHARACTER_ACTION_UPDATE:
            _actionSystem.changeAction( sessionId, character, payload );
            break;

        case Message::MessageReceiverType::COMBAT_ROOM_CREATE:
            createCombat( sessionId, character );
            break;
        case Message::MessageReceiverType::COMBAT_ROOM_ENTER: {
            std::string roomId = payload[ "id" ].asString();
            enterCombat( sessionId, character, roomId );
            break;
        }
        case Message::MessageReceiverType::COMBAT_ROOM_EXIT:
            exitCombat( sessionId );
            break;
        default:
            break;
    }
}

} // namespace Core::Instance
