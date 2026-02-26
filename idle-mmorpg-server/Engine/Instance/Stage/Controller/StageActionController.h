#ifndef STAGEACTIONCONTROLLER_H
#define STAGEACTIONCONTROLLER_H

#include <Domain/Stage/Stage.h>
#include <Engine/Manager/Action/ActionManager.h>

#include "StageController.h"

namespace Engine {

class StageActionController : public StageController {
public:
    explicit StageActionController( Domain::Stage* stage,
                                    Manager::ActionManager& actionManager );

    void onCharacterEnter( CharacterInstance* characterInstance ) override;
    void onCharacterExit( const std::string& sessionId ) override;

    void onTick() override;

    void handleMessage( CharacterInstance* characterInstance, MessageReceiverType type, const Json::Value& payload ) override;

private:
    Manager::ActionManager& _actionManager;
};

} // namespace Engine

#endif // STAGEACTIONCONTROLLER_H
