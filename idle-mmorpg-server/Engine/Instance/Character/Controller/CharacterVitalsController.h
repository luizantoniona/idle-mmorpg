#ifndef CHARACTERVITALSCONTROLLER_H
#define CHARACTERVITALSCONTROLLER_H

#include <Domain/Character/CharacterVitals.h>

#include "CharacterController.h"

namespace Engine {

class CharacterVitalsController : public CharacterController {
public:
    explicit CharacterVitalsController( Domain::CharacterVitals& vitals );

    void onEnterWorld() override;
    void onTickWorld() override;
    void onExitWorld() override;

private:
    Domain::CharacterVitals& _vitals;
};

} // namespace Engine

#endif // CHARACTERVITALSCONTROLLER_H
