#ifndef CHARACTERSTAGECONTROLLER_H
#define CHARACTERSTAGECONTROLLER_H

#include <Domain/Character/Character.h>

#include "CharacterController.h"

namespace Engine {

class CharacterStageController : public CharacterController {
public:
    explicit CharacterStageController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                       Domain::Character& character );

    void onEnterWorld() override;
    void onLeaveWorld() override;

    void onTick() override;

    void handleMessage( MessageReceiverType type, const Json::Value& payload ) override;

private:
    // -- Message methods ---
    void handleNextStage();

    // --- EventBus methods ---
    void onCreatureKilled( const CharacterEvent& event );

    void updateStageCompletion();

private:
    Domain::CharacterStage& _characterStage;
};

} // namespace Engine

#endif // CHARACTERSTAGECONTROLLER_H
