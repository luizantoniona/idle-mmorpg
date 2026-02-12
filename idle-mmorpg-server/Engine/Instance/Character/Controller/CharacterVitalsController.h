#ifndef CHARACTERVITALSCONTROLLER_H
#define CHARACTERVITALSCONTROLLER_H

#include <Domain/Character/CharacterVitals.h>

namespace Engine {

class CharacterVitalsController {
public:
    explicit CharacterVitalsController( Domain::CharacterVitals& vitals );

    void onEnterWorld();
    void onExitWorld();

    void tick();

private:
    Domain::CharacterVitals& _vitals;
};

} // namespace Engine

#endif // CHARACTERVITALSCONTROLLER_H
