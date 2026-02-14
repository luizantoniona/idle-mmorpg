#include "CharacterEffectsController.h"

namespace Engine {

CharacterEffectsController::CharacterEffectsController( Domain::CharacterEffects& effects ) :
    _effects( effects ) {}

void CharacterEffectsController::onEnterWorld() {}

void CharacterEffectsController::onTickWorld() {
}

void CharacterEffectsController::onExitWorld() {}

} // namespace Engine
