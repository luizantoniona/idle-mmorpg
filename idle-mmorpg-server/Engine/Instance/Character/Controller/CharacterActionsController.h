#ifndef CHARACTERACTIONSCONTROLLER_H
#define CHARACTERACTIONSCONTROLLER_H

#include <Domain/Character/CharacterActions.h>
#include <Manager/Action/ActionManager.h>

namespace Engine {

class CharacterActionsController {
public:
    explicit CharacterActionsController( Domain::CharacterActions& actions, Manager::ActionManager& actionManager );

    void onEnterWorld();
    void onExitWorld();

    void tick();

private:
    Domain::CharacterActions& _actions;
    Manager::ActionManager& _actionManager;
};

} // namespace Engine

#endif // CHARACTERACTIONSCONTROLLER_H
