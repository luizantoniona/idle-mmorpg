#ifndef CHARACTEREFFECTSCONTROLLER_H
#define CHARACTEREFFECTSCONTROLLER_H

#include <Domain/Character/CharacterEffects.h>

namespace Engine {

class CharacterEffectsController {
public:
    explicit CharacterEffectsController( Domain::CharacterEffects& effects );

    void onEnterWorld();
    void onExitWorld();

    void tick();

private:
    Domain::CharacterEffects& _effects;
};

} // namespace Engine

#endif // CHARACTEREFFECTSCONTROLLER_H
