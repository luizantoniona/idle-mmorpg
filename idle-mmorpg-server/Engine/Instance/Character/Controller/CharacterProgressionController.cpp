#include "CharacterProgressionController.h"

namespace Engine {

CharacterProgressionController::CharacterProgressionController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                                Domain::Character& character ) :
    CharacterController( eventBus, messageSender ),
    _characterProgression( character.progression() ) {
}

void CharacterProgressionController::onEnterWorld() {
    _messageSender.sendMessage( MessageSenderType::CHARACTER_PROGRESSION, _characterProgression.toJson() );
}

void CharacterProgressionController::onLeaveWorld() {
}

void CharacterProgressionController::onTick() {
}

} // namespace Engine
