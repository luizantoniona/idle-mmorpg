#ifndef STAGEINSTANCE_H
#define STAGEINSTANCE_H

#include <mutex>
#include <unordered_map>

#include <Domain/Stage/Stage.h>
#include <Engine/Message/MessageReceiverType.h>

#include <Engine/Instance/Character/CharacterInstance.h>
#include <Engine/Instance/Combat/CombatInstance.h>

namespace Engine {

class StageInstance {
public:
    explicit StageInstance( Domain::Stage* stage );

    Domain::Stage* stage();

    bool addCharacter( const std::string& sessionId, CharacterInstance* characterInstance );
    void removeCharacter( const std::string& sessionId );

    void createCombat( const std::string& sessionId, CharacterInstance* characterInstance );
    void enterCombat( const std::string& sessionId, CharacterInstance* characterInstance, const std::string& roomId );
    void exitCombat( const std::string& sessionId );

    void tick();

    void handleCharacterMessage( const std::string& sessionId, MessageReceiverType type, const Json::Value& payload );

private:
    mutable std::mutex _mutex;
    Domain::Stage* _stage;

    std::unordered_map<std::string, CharacterInstance*> _characters;
    std::unordered_map<std::string, CombatInstance*> _characterCombatCache;
    std::vector<std::unique_ptr<CombatInstance>> _combatInstances;
};

} // namespace Engine

#endif // STAGEINSTANCE_H
