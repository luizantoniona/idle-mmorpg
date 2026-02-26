#ifndef STAGECONTROLLER_H
#define STAGECONTROLLER_H

#include <Engine/Instance/Character/CharacterInstance.h>

#include <Domain/Stage/Stage.h>

namespace Engine {

class StageController {
public:
    explicit StageController( Domain::Stage* stage );
    virtual ~StageController();

    virtual void onCharacterEnter( CharacterInstance* characterInstance ) = 0;
    virtual void onCharacterExit( const std::string& sessionId ) = 0;

    virtual void onTick() = 0;

    virtual void handleMessage( CharacterInstance* characterInstance, MessageReceiverType type, const Json::Value& payload );

protected:
    Domain::Stage* _stage;
};

} // namespace Engine

#endif // STAGECONTROLLER_H
