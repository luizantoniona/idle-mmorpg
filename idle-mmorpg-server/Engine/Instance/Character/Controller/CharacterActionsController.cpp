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

void CharacterActionsController::onTickWorld() {
}

void CharacterActionsController::onExitWorld() {
}

} // namespace Engine
