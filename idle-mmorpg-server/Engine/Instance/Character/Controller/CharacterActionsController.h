#ifndef CHARACTERACTIONSCONTROLLER_H
#define CHARACTERACTIONSCONTROLLER_H

#include <Domain/Character/CharacterActions.h>
#include <Engine/Manager/Action/ActionManager.h>

#include "CharacterController.h"

namespace Engine {

class CharacterActionsController : public CharacterController {
public:
    explicit CharacterActionsController( std::function<void( MessageSenderType, const Json::Value& )> sendMessage,
                                         Domain::CharacterActions& actions,
                                         Manager::ActionManager& actionManager );

    void onEnterWorld() override;
    void onLeaveWorld() override;

    void onTick() override;

private:
    Domain::CharacterActions& _actions;
    Manager::ActionManager& _actionManager;
};

} // namespace Engine

#endif // CHARACTERACTIONSCONTROLLER_H
