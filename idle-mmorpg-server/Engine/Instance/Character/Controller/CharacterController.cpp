#include "CharacterController.h"

namespace Engine {

CharacterController::CharacterController( std::function<void( MessageSenderType, const Json::Value& )> sendMessage ) :
    _sendMessage( std::move( sendMessage ) ) {
}

CharacterController::~CharacterController() = default;

void CharacterController::sendMessage( MessageSenderType type, const Json::Value& payload ) {
    if ( _sendMessage ) {
        _sendMessage( type, payload );
    }
}

void CharacterController::handleMessage( MessageReceiverType, const Json::Value& ) {
    return;
}

} // namespace Engine
