#include "CharacterEffectsController.h"

namespace Engine {

CharacterEffectsController::CharacterEffectsController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                        Domain::Character& character ) :
    CharacterController( eventBus, messageSender ),
    _characterEffects( character.effects() ) {
}

void CharacterEffectsController::onEnterWorld() {
    _messageSender.sendMessage( MessageSenderType::CHARACTER_EFFECTS, _characterEffects.toJson() );
}

void CharacterEffectsController::onLeaveWorld() {
}

void CharacterEffectsController::onTick() {
}

} // namespace Engine
