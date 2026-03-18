#include "CharacterStageController.h"

namespace Engine {

CharacterStageController::CharacterStageController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                    Domain::Character& character ) :
    CharacterController( eventBus, messageSender ),
    _characterStage( character.stage() ) {
}

void CharacterStageController::onEnterWorld() {
    _messageSender.sendMessage( MessageSenderType::CHARACTER_STAGE, _characterStage.toJson() );
}

void CharacterStageController::onLeaveWorld() {
}

void CharacterStageController::onTick() {
}

} // namespace Engine
