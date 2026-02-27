#include "CharacterVitalsController.h"

namespace Engine {

CharacterVitalsController::CharacterVitalsController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                      Domain::CharacterVitals& vitals ) :
    CharacterController( eventBus, messageSender ),
    _vitals( vitals ) {
}

void CharacterVitalsController::onEnterWorld() {
    _messageSender.sendMessage( MessageSenderType::CHARACTER_VITALS, _vitals.toJson() );
}

void CharacterVitalsController::onLeaveWorld() {
}

void CharacterVitalsController::onTick() {
}

} // namespace Engine
