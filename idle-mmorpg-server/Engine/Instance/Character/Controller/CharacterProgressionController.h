#ifndef CHARACTERPROGRESSIONCONTROLLER_H
#define CHARACTERPROGRESSIONCONTROLLER_H

#include <Domain/Character/CharacterProgression.h>

#include "CharacterController.h"

namespace Engine {

class CharacterProgressionController : public CharacterController {
public:
    explicit CharacterProgressionController( std::function<void( MessageSenderType, const Json::Value& )> sendMessage,
                                             Domain::CharacterProgression& progression );

    void onEnterWorld() override;
    void onLeaveWorld() override;

    void onTick() override;

private:
    Domain::CharacterProgression& _progression;
};

} // namespace Engine

#endif // CHARACTERPROGRESSIONCONTROLLER_H
