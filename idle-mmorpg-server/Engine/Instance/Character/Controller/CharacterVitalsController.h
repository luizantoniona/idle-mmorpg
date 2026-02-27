#ifndef CHARACTERVITALSCONTROLLER_H
#define CHARACTERVITALSCONTROLLER_H

#include <Domain/Character/CharacterVitals.h>

#include "CharacterController.h"

namespace Engine {

class CharacterVitalsController : public CharacterController {
public:
    explicit CharacterVitalsController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                        Domain::CharacterVitals& vitals );

    void onEnterWorld() override;
    void onLeaveWorld() override;

    void onTick() override;

private:
    Domain::CharacterVitals& _vitals;
};

} // namespace Engine

#endif // CHARACTERVITALSCONTROLLER_H
