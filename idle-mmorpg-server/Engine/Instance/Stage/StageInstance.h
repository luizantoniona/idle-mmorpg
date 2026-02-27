#ifndef STAGEINSTANCE_H
#define STAGEINSTANCE_H

#include <mutex>
#include <unordered_map>

#include <Domain/Stage/Stage.h>
#include <Engine/Message/MessageReceiverType.h>
#include <Engine/Instance/Character/CharacterInstance.h>

#include "Controller/StageCombatController.h"

namespace Engine {

class StageInstance {
public:
    explicit StageInstance( Domain::Stage* stage );

    bool addCharacter( const std::string& sessionId, CharacterInstance* characterInstance );
    void removeCharacter( const std::string& sessionId );

    void tick();

    void handleMessage( CharacterInstance* character, MessageReceiverType type, const Json::Value& payload );

private:
    mutable std::mutex _mutex;
    Domain::Stage* _stage;
    std::unordered_map<std::string, CharacterInstance*> _characters;

    std::vector<StageController*> _controllers;
    std::unique_ptr<StageCombatController> _combatController;
};

} // namespace Engine

#endif // STAGEINSTANCE_H
