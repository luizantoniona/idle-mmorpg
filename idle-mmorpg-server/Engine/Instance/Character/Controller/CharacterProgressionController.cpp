#include "CharacterProgressionController.h"

namespace Engine {

CharacterProgressionController::CharacterProgressionController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                                Domain::CharacterProgression& progression ) :
    CharacterController( eventBus, messageSender ),
    _progression( progression ) {
}

void CharacterProgressionController::onEnterWorld() {
    _messageSender.sendMessage( MessageSenderType::CHARACTER_PROGRESSION, _progression.toJson() );
}

void CharacterProgressionController::onLeaveWorld() {
}

void CharacterProgressionController::onTick() {
}

} // namespace Engine
