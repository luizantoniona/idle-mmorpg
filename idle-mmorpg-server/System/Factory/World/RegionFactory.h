#ifndef REGIONFACTORY_H
#define REGIONFACTORY_H

#include <string>

#include <json/json.h>

#include <Model/World/Region.h>
#include <Model/World/RegionConnection.h>

namespace System::Factory {

class RegionFactory {
public:
    static std::unique_ptr<Model::Region> createRegion( const std::string& regionName, const std::string& regionPath );
    static std::unique_ptr<Model::RegionConnection> createRegionConnection( const Json::Value& connectionJson );
};

} // namespace System::Factory

#endif // REGIONFACTORY_H
