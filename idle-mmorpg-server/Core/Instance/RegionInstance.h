#ifndef REGIONINSTANCE_H
#define REGIONINSTANCE_H

#include <memory>
#include <string>
#include <unordered_map>

#include <Model/World/Region.h>

#include "LocationInstance.h"

namespace Core::Instance {

class RegionInstance {
public:
    explicit RegionInstance( Model::Region* region );

    bool addCharacter( const std::string& sessionId, Model::Character* character );
    void removeCharacter( const std::string& sessionId );
    void moveCharacter( const std::string& sessionId, const std::string& destination );

    LocationInstance* characterLocationInstance( const std::string& sessionId );

    void tick();

    void handleCharacterMessage( const std::string& sessionId, Message::MessageReceiverType type, const Json::Value& payload );

private:
    mutable std::recursive_mutex _mutex;
    Model::Region* _region;
    std::unordered_map<std::string, std::unique_ptr<LocationInstance> > _locations;
    std::unordered_map<std::string, Model::Character*> _characters;
    std::unordered_map<std::string, LocationInstance*> _characterToLocation;
};

} // namespace Core::Instance

#endif // REGIONINSTANCE_H
