#include "CharacterActionsController.h"

namespace Engine {

CharacterActionsController::CharacterActionsController( std::function<void( MessageSenderType, const Json::Value& )> sendMessage,
                                                        Domain::CharacterActions& actions,
                                                        Manager::ActionManager& actionManager ) :
    CharacterController( sendMessage ),
    _actions( actions ),
    _actionManager( actionManager ) {
}

void CharacterActionsController::onEnterWorld() {
    sendMessage( MessageSenderType::CHARACTER_ACTIONS, _actions.toJson() );
}

void CharacterActionsController::onLeaveWorld() {
}

void CharacterActionsController::onTick() {
    if ( _actions.currentAction().type() == Domain::ActionType::UNKNOWN ) {
        return;
    }

    if ( _actions.counter() < _actions.duration() ) {
        _actions.setCounter( _actions.counter() + 1 );

        sendMessage( MessageSenderType::CHARACTER_ACTIONS, _actions.toJson() );
        return;
    }
}

void CharacterActionsController::handleMessage( MessageReceiverType type, const Json::Value& payload ) {
    switch ( type ) {
    case MessageReceiverType::CHARACTER_SET_ACTION:
        sendMessage( MessageSenderType::CHARACTER_ACTIONS, _actions.toJson() );
    default:
        break;
    }
}

} // namespace Engine
