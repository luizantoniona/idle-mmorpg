#include "CharacterEffectsController.h"

namespace Engine {

CharacterEffectsController::CharacterEffectsController( std::function<void( MessageSenderType, const Json::Value& )> sendMessage,
                                                        Domain::CharacterEffects& effects ) :
    CharacterController( sendMessage ),
    _effects( effects ) {
}

void CharacterEffectsController::onEnterWorld() {
    sendMessage( MessageSenderType::CHARACTER_EFFECTS, _effects.toJson() );
}

void CharacterEffectsController::onLeaveWorld() {
}

void CharacterEffectsController::onTick() {
}

} // namespace Engine
