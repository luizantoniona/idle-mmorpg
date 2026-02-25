#ifndef STAGEACTIONCONTROLLER_H
#define STAGEACTIONCONTROLLER_H

#include <Domain/Stage/Stage.h>

#include "StageController.h"

namespace Engine {

class StageActionController : public StageController {
public:
    explicit StageActionController( Domain::Stage* stage );

    void onCharacterEnter( CharacterInstance* characterInstance ) override;
    void onCharacterExit( const std::string& sessionId ) override;

    void onTick() override;
};

} // namespace Engine

#endif // STAGEACTIONCONTROLLER_H
