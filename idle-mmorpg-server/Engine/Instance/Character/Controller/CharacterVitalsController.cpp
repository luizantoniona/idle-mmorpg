#include "CharacterVitalsController.h"

namespace Engine {

CharacterVitalsController::CharacterVitalsController( std::function<void( MessageSenderType, const Json::Value& )> sendMessage,
                                                      Domain::CharacterVitals& vitals ) :
    CharacterController( sendMessage ),
    _vitals( vitals ) {
}

void CharacterVitalsController::onEnterWorld() {
    sendMessage( MessageSenderType::CHARACTER_VITALS, _vitals.toJson() );
}

void CharacterVitalsController::onLeaveWorld() {
}

void CharacterVitalsController::onTick() {
}

} // namespace Engine
