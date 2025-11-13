#ifndef WORLDINSTANCE_H
#define WORLDINSTANCE_H

#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

#include <Domain/World/World.h>

#include "LocationInstance.h"

namespace Engine {

class WorldInstance {
public:
    explicit WorldInstance( Domain::World* world );

    bool addCharacter( const std::string& sessionId, std::unique_ptr<Domain::Character> character );
    void removeCharacter( const std::string& sessionId );
    void moveCharacter( const std::string& sessionId, const std::string& destination );
    bool hasCharacter( const int idCharacter );

    LocationInstance* characterLocationInstance( const std::string& sessionId );

    void tick();

    void handleCharacterMessage( const std::string& sessionId, Engine::MessageReceiverType type, const Json::Value& payload );

private:
    mutable std::mutex _mutex;
    Domain::World* _world;
    std::unordered_map<std::string, std::unique_ptr<LocationInstance> > _locations;
    std::unordered_map<std::string, std::unique_ptr<Domain::Character>> _characters;
    std::unordered_map<std::string, LocationInstance*> _characterToLocation;
};

} // namespace Engine

#endif // WORLDINSTANCE_H
