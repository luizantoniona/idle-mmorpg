#include "LocationInstance.h"

#include <iostream>

#include <Core/Message/MessageSenderType.h>
#include <Core/System/ActionSystem.h>

namespace Core::Instance {

LocationInstance::LocationInstance( Model::Location* location ) :
    _mutex(),
    _location( location ),
    _characters( {} ),
    _notificationSystem(),
    _actionSystem( location ),
    _combatSystem( location ),
    _trainingSystem( location ) {}

bool LocationInstance::addCharacter( const std::string& sessionId, Model::Character* character ) {
    std::lock_guard lock( _mutex );
    _characters[sessionId] = character;

    std::cout << "LocationInstance::addCharacter"
              << " [Character] " << character->name()
              << " [Entering] " << _location->name()
              << " [SessionID] " << sessionId << std::endl;

    _notificationSystem.notifyFullCharacter( sessionId, character );
    _notificationSystem.notifyFullLocation( sessionId, _location );
    _notificationSystem.notifyLocationActions( sessionId, character, _location );

    return true;
}

void LocationInstance::removeCharacter( const std::string& sessionId ) {
    std::lock_guard lock( _mutex );
    std::cout << "LocationInstance::removeCharacter" << " [SessionID] " << sessionId << std::endl;
    _characters.erase( sessionId );
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
            _combatSystem.process( sessionId, character );
            continue;
        }

        _actionSystem.process( sessionId, character );
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
        case Message::MessageReceiverType::CHARACTER_UPDATE_STRUCTURE:
            _actionSystem.changeStructure( sessionId, character, payload );
            break;
        case Message::MessageReceiverType::CHARACTER_UPDATE_ACTION:
            _actionSystem.changeAction( sessionId, character, payload );
            break;
        default:
            break;
    }
}

} // namespace Core::Instance
