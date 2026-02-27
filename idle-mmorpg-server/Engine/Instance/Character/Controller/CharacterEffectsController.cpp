#include "CharacterEffectsController.h"

namespace Engine {

CharacterEffectsController::CharacterEffectsController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                        Domain::CharacterEffects& effects ) :
    CharacterController( eventBus, messageSender ),
    _effects( effects ) {
}

void CharacterEffectsController::onEnterWorld() {
    _messageSender.sendMessage( MessageSenderType::CHARACTER_EFFECTS, _effects.toJson() );
}

void CharacterEffectsController::onLeaveWorld() {
}

void CharacterEffectsController::onTick() {
}

} // namespace Engine
