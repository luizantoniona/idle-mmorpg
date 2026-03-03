#include "CharacterProgressionController.h"

namespace Engine {

CharacterProgressionController::CharacterProgressionController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                                Domain::Character& character,
                                                                Manager::ServerConfigurationManager& configurationManager ) :
    CharacterController( eventBus, messageSender ),
    _characterProgression( character.progression() ),
    _configurationManager( configurationManager ) {
}

void CharacterProgressionController::onEnterWorld() {
    _characterProgression.setBaseExperience( _configurationManager.baseExperience() );
    _characterProgression.setGrowthRate( _configurationManager.growthRate() );

    _messageSender.sendMessage( MessageSenderType::CHARACTER_PROGRESSION, _characterProgression.toJson() );
}

void CharacterProgressionController::onLeaveWorld() {
}

void CharacterProgressionController::onTick() {
}

} // namespace Engine
