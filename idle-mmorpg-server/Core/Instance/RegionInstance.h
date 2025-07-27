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
    void moveCharacter( const std::string& sessionId );

    LocationInstance* characterLocationInstance( const std::string& sessionId );

    void tick();

private:
    mutable std::mutex _mutex;
    System::Message::MessageSender _sender;
    std::unordered_map<std::string, Model::Character*> _characters;
    Model::Region* _region;
    std::unordered_map<std::string, std::unique_ptr<LocationInstance> > _locations;
    std::unordered_map<std::string, LocationInstance*> _characterToLocation;
};

} // namespace Core::Instance

#endif // REGIONINSTANCE_H
