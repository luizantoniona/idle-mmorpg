#ifndef LOCATIONFACTORY_H
#define LOCATIONFACTORY_H

#include <string>

#include <json/json.h>

#include <Domain/World/Location/Location.h>
#include <Domain/World/Location/LocationConnection.h>

namespace Engine {

class LocationFactory {
public:
    static std::unique_ptr<Domain::Location> createLocation( const std::string& locationName, const std::string& locationPath );
};

} // namespace Engine

#endif // LOCATIONFACTORY_H
