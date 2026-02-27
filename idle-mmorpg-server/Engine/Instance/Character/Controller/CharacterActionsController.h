#ifndef CHARACTERACTIONSCONTROLLER_H
#define CHARACTERACTIONSCONTROLLER_H

#include <Domain/Character/Character.h>
#include <Engine/Manager/Action/ActionManager.h>

#include "CharacterController.h"

namespace Engine {

class CharacterActionsController : public CharacterController {
public:
    explicit CharacterActionsController( std::function<void( MessageSenderType, const Json::Value& )> sendMessage,
                                         Domain::Character& character,
                                         Manager::ActionManager& actionManager );

    void onEnterWorld() override;
    void onLeaveWorld() override;

    void onTick() override;

    void handleMessage( MessageReceiverType type, const Json::Value& payload ) override;

    void refreshAvailableActions( int stageLevel );
    void handleActionMessage( const Json::Value& payload, int stageLevel );

private:
    Domain::Character& _character;
    Manager::ActionManager& _actionManager;

    void executeCurrentAction();

    void executeTraining( const Domain::CharacterActionOption& option );

    std::vector<Domain::SkillType> combatSkill( Domain::Character* character );
};

} // namespace Engine

#endif // CHARACTERACTIONSCONTROLLER_H
