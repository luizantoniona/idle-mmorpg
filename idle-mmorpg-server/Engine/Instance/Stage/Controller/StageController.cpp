#include "StageController.h"

#include <iostream>

namespace Engine {

StageController::StageController( Domain::Stage* stage ) :
    _stage( stage ) {
}

StageController::~StageController() = default;

void StageController::handleMessage( CharacterInstance* characterInstance, MessageReceiverType type, const Json::Value& payload ) {
    std::cout << "StageController::handleMessage - Not implemented - MessageType: " << static_cast<int>( type ) << " Payload: " << payload << std::endl;
}

} // namespace Engine
