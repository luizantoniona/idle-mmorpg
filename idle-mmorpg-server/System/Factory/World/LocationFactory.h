#ifndef LOCATIONFACTORY_H
#define LOCATIONFACTORY_H

#include <string>

#include <json/json.h>

#include <Model/World/Location/LocationConnection.h>
#include <Model/World/Location/Location.h>

namespace System::Factory {

class LocationFactory {
public:
    static std::unique_ptr<Model::Location> createLocation( const std::string& locationName, const std::string& locationPath );
    static std::unique_ptr<Model::LocationConnection> createLocationConnection( const Json::Value& connectionJson );
};

} // namespace System::Factory

#endif // LOCATIONFACTORY_H
