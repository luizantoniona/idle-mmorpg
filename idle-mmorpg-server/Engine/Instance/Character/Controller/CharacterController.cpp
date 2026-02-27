#include "CharacterController.h"

#include <iostream>

namespace Engine {

CharacterController::CharacterController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender ) :
    _eventBus( eventBus ),
    _messageSender( messageSender ) {
}

CharacterController::~CharacterController() = default;

void CharacterController::handleMessage( MessageReceiverType type, const Json::Value& payload ) {
    std::cout << "CharacterController::handleMessage - Not implemented - MessageType: " << static_cast<int>( type ) << " Payload: " << payload << std::endl;
}

} // namespace Engine
