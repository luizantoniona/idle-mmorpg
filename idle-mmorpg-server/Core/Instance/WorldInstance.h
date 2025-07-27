#ifndef WORLDINSTANCE_H
#define WORLDINSTANCE_H

#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

#include <Model/World/World.h>

#include "RegionInstance.h"

namespace Core::Instance {

class WorldInstance {
public:
    explicit WorldInstance( Model::World* world );

    bool addCharacter( const std::string& sessionId, std::unique_ptr<Model::Character> character );
    void removeCharacter( const std::string& sessionId );
    void moveCharacter( const std::string& sessionId );
    bool hasCharacter( const int idCharacter );

    RegionInstance* characterRegionInstance( const std::string& sessionId );
    LocationInstance* characterLocationInstance( const std::string& sessionId );

    void tick();

private:
    mutable std::mutex _mutex;
    System::Message::MessageSender _sender;
    std::unordered_map<std::string, std::unique_ptr<Model::Character> > _characters;
    Model::World* _world;
    std::unordered_map<std::string, std::unique_ptr<RegionInstance> > _regions;
    std::unordered_map<std::string, RegionInstance*> _characterToRegion;
};

} // namespace Core::Instance

#endif // WORLDINSTANCE_H
