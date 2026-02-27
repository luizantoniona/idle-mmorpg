#ifndef CHARACTERPROGRESSIONCONTROLLER_H
#define CHARACTERPROGRESSIONCONTROLLER_H

#include <Domain/Character/Character.h>

#include "CharacterController.h"

namespace Engine {

class CharacterProgressionController : public CharacterController {
public:
    explicit CharacterProgressionController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                             Domain::Character& character );

    void onEnterWorld() override;
    void onLeaveWorld() override;

    void onTick() override;

private:
    Domain::CharacterProgression& _characterProgression;
};

} // namespace Engine

#endif // CHARACTERPROGRESSIONCONTROLLER_H
