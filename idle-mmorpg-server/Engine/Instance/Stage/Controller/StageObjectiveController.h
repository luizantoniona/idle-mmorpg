#ifndef STAGEOBJECTIVECONTROLLER_H
#define STAGEOBJECTIVECONTROLLER_H

#include <Domain/Stage/Stage.h>

#include "StageController.h"

namespace Engine {

class StageObjectiveController : public StageController {
public:
    explicit StageObjectiveController( Domain::Stage* stage );

    void onCharacterEnter( CharacterInstance* characterInstance ) override;
    void onCharacterExit( const std::string& sessionId ) override;

    void onTick() override;
};

} // namespace Engine

#endif // STAGEOBJECTIVECONTROLLER_H
