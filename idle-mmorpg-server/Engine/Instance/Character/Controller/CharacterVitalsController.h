#ifndef CHARACTERVITALSCONTROLLER_H
#define CHARACTERVITALSCONTROLLER_H

#include <Domain/Character/Character.h>

#include "CharacterController.h"

namespace Engine {

class CharacterVitalsController : public CharacterController {
public:
    explicit CharacterVitalsController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                        Domain::Character& character );

    void onEnterWorld() override;
    void onLeaveWorld() override;

    void onTick() override;

private:
    Domain::CharacterVitals& _characterVitals;
};

} // namespace Engine

#endif // CHARACTERVITALSCONTROLLER_H
