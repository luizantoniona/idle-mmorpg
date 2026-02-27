#include "StageActionController.h"

namespace Engine {

StageActionController::StageActionController( Domain::Stage* stage ) :
    StageController( stage ) {
}

void StageActionController::onCharacterEnter( CharacterInstance* characterInstance ) {
    characterInstance->actionsController()->refreshAvailableActions( _stage->level() );
}
void StageActionController::onCharacterExit( const std::string& sessionId ) {
}

void StageActionController::onTick() {
}

void StageActionController::handleMessage( CharacterInstance* characterInstance, MessageReceiverType type, const Json::Value& payload ) {
    if ( type != MessageReceiverType::CHARACTER_SET_ACTION ) {
        return;
    }
    characterInstance->actionsController()->handleActionMessage( payload, _stage->level() );
}

} // namespace Engine
