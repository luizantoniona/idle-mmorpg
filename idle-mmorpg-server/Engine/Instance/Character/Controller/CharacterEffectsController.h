#ifndef CHARACTEREFFECTSCONTROLLER_H
#define CHARACTEREFFECTSCONTROLLER_H

#include <Domain/Character/CharacterEffects.h>

#include "CharacterController.h"

namespace Engine {

class CharacterEffectsController : public CharacterController {
public:
    explicit CharacterEffectsController( Domain::CharacterEffects& effects );

    void onEnterWorld() override;
    void onTickWorld() override;
    void onExitWorld() override;

private:
    Domain::CharacterEffects& _effects;
};

} // namespace Engine

#endif // CHARACTEREFFECTSCONTROLLER_H
