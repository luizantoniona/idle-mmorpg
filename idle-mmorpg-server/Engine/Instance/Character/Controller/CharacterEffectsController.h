#ifndef CHARACTEREFFECTSCONTROLLER_H
#define CHARACTEREFFECTSCONTROLLER_H

namespace Engine {

class CharacterEffectsController {
public:
    CharacterEffectsController();

    void onEnterWorld();
    void onExitWorld();

    void tick();
};

} // namespace Engine

#endif // CHARACTEREFFECTSCONTROLLER_H
