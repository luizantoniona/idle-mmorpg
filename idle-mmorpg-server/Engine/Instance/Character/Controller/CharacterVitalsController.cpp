#include "CharacterVitalsController.h"

namespace Engine {

CharacterVitalsController::CharacterVitalsController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                      Domain::Character& character ) :
    CharacterController( eventBus, messageSender ),
    _characterVitals( character.vitals() ) {
}

void CharacterVitalsController::onEnterWorld() {
    _messageSender.sendMessage( MessageSenderType::CHARACTER_VITALS, _characterVitals.toJson() );
}

void CharacterVitalsController::onLeaveWorld() {
}

void CharacterVitalsController::onTick() {
}

} // namespace Engine
