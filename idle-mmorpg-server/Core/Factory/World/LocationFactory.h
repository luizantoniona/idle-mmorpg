#ifndef LOCATIONFACTORY_H
#define LOCATIONFACTORY_H

#include <string>

#include <json/json.h>

#include <Model/World/Location/LocationConnection.h>
#include <Model/World/Location/Location.h>

namespace Core::Factory {

class LocationFactory {
public:
    static std::unique_ptr<Model::Location> createLocation( const std::string& locationName, const std::string& locationPath );
};

} // namespace Core::Factory

#endif // LOCATIONFACTORY_H
