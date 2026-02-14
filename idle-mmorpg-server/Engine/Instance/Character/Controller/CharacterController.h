#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H

namespace Engine {

class CharacterController {
public:
    CharacterController();

    virtual void onEnterWorld() = 0;
    virtual void onTickWorld() = 0;
    virtual void onExitWorld() = 0;
};

} // namespace Engine

#endif // CHARACTERCONTROLLER_H
