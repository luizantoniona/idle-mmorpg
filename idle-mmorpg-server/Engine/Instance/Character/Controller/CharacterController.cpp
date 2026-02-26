#include "CharacterController.h"

#include <iostream>

namespace Engine {

CharacterController::CharacterController( std::function<void( MessageSenderType, const Json::Value& )> sendMessage ) :
    _sendMessage( std::move( sendMessage ) ) {
}

CharacterController::~CharacterController() = default;

void CharacterController::handleMessage( MessageReceiverType type, const Json::Value& payload ) {
    std::cout << "CharacterController::handleMessage - Not implemented - MessageType: " << static_cast<int>( type ) << " Payload: " << payload << std::endl;
}

void CharacterController::sendMessage( MessageSenderType type, const Json::Value& payload ) {
    if ( _sendMessage ) {
        _sendMessage( type, payload );
    }
}

} // namespace Engine
