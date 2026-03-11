#ifndef CHARACTEREFFECTSCONTROLLER_H
#define CHARACTEREFFECTSCONTROLLER_H

#include <Domain/Character/Character.h>

#include "CharacterController.h"

namespace Engine {

class CharacterEffectsController : public CharacterController {
public:
    explicit CharacterEffectsController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                         Domain::Character& character );

    void onEnterWorld() override;
    void onLeaveWorld() override;

    void onTick() override;

private:
    // --- EventBus methods ---
    void onApplyEffect( const CharacterEvent& event );

private:
    Domain::CharacterEffects& _characterEffects;
};

} // namespace Engine

#endif // CHARACTEREFFECTSCONTROLLER_H
