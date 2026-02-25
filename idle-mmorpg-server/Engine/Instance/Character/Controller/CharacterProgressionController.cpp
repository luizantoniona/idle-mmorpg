#include "CharacterProgressionController.h"

namespace Engine {

CharacterProgressionController::CharacterProgressionController( std::function<void( MessageSenderType, const Json::Value& )> sendMessage,
                                                                Domain::CharacterProgression& progression ) :
    CharacterController( sendMessage ),
    _progression( progression ) {
}

void CharacterProgressionController::onEnterWorld() {
    sendMessage( MessageSenderType::CHARACTER_PROGRESSION, _progression.toJson() );
}

void CharacterProgressionController::onLeaveWorld() {
}

void CharacterProgressionController::onTick() {
}

} // namespace Engine
