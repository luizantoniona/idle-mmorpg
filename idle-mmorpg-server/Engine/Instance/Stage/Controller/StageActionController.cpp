#include "StageActionController.h"

namespace Engine {

StageActionController::StageActionController( Domain::Stage* stage ) :
    StageController( stage ) {
}

void StageActionController::onCharacterEnter( CharacterInstance* characterInstance ) {
}

void StageActionController::onCharacterExit( const std::string& sessionId ) {
}

void StageActionController::onTick() {
}

} // namespace Engine
