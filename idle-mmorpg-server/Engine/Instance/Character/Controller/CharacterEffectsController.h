#ifndef CHARACTEREFFECTSCONTROLLER_H
#define CHARACTEREFFECTSCONTROLLER_H

#include <Domain/Character/CharacterEffects.h>

#include "CharacterController.h"

namespace Engine {

class CharacterEffectsController : public CharacterController {
public:
    explicit CharacterEffectsController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                         Domain::CharacterEffects& effects );

    void onEnterWorld() override;
    void onLeaveWorld() override;

    void onTick() override;

private:
    Domain::CharacterEffects& _effects;
};

} // namespace Engine

#endif // CHARACTEREFFECTSCONTROLLER_H
