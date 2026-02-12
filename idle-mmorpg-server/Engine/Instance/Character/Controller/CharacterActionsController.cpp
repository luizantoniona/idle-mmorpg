#include "CharacterActionsController.h"

namespace Engine {

CharacterActionsController::CharacterActionsController( Domain::CharacterActions& actions, Manager::ActionManager& actionManager ) :
    _actions( actions ),
    _actionManager( actionManager ) {}

void CharacterActionsController::onEnterWorld() {}

void CharacterActionsController::onExitWorld() {}

void CharacterActionsController::tick() {}

} // namespace Engine
