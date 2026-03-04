#ifndef WORLDINSTANCE_H
#define WORLDINSTANCE_H

#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

#include <Domain/World/World.h>
#include <Engine/Instance/Character/CharacterInstance.h>
#include <Engine/Instance/Stage/StageInstance.h>

namespace Engine {

class WorldInstance {
public:
    explicit WorldInstance( Domain::World* world );

    bool hasCharacter( const int idCharacter );
    bool addCharacter( const std::string& sessionId, std::unique_ptr<CharacterInstance> characterInstance );
    void removeCharacter( const std::string& sessionId );

    StageInstance* characterStageInstance( const std::string& sessionId );

    void tick();

    void handleMessage( const std::string& sessionId, const Json::Value& messageJson );

private:
    mutable std::mutex _mutex;
    Domain::World* _world;
    std::unordered_map<std::string, std::unique_ptr<CharacterInstance>> _characters;
    std::unordered_map<int, std::unique_ptr<StageInstance>> _stages;
    std::unordered_map<std::string, StageInstance*> _characterToStage;
};

} // namespace Engine

#endif // WORLDINSTANCE_H
