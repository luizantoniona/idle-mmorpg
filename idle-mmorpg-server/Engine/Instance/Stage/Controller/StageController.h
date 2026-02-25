#ifndef STAGECONTROLLER_H
#define STAGECONTROLLER_H

#include <unordered_map>

#include <Engine/Instance/Character/CharacterInstance.h>

#include <Domain/Stage/Stage.h>

namespace Engine {

class StageController {
public:
    StageController( Domain::Stage* stage );

    virtual void onCharacterEnter() = 0;
    virtual void onCharacterExit() = 0;

    virtual void onTick() = 0;

private:
    Domain::Stage* _stage;
    std::unordered_map<std::string, CharacterInstance*> _characters;
};

} // namespace Engine

#endif // STAGECONTROLLER_H
