#include "CharacterEffectsController.h"

namespace Engine {

CharacterEffectsController::CharacterEffectsController( Domain::CharacterEffects& effects ) :
    _effects( effects ) {}

void CharacterEffectsController::onEnterWorld() {}

void CharacterEffectsController::onExitWorld() {}

void CharacterEffectsController::tick() {}

} // namespace Engine
