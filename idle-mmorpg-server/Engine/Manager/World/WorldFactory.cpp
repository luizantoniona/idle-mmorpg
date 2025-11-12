#include "WorldFactory.h"

#include <iostream>

#include <Shared/Helper/JsonHelper.h>

#include "LocationFactory.h"

namespace Engine {

std::unique_ptr<Domain::World> WorldFactory::createWorld( const std::string& mapPath ) {
    std::cout << "WorldFactory::createWorld" << std::endl;

    std::unique_ptr<Domain::World> world = std::make_unique<Domain::World>();

    Json::Value worldConfig = Helper::JsonHelper::loadJsonFile( mapPath + "world.json" );

    if ( !worldConfig.isMember( "locations" ) || !worldConfig["locations"].isArray() ) {
        std::cerr << "WorldFactory::createWorld missing or invalid 'locations' array in world.json" << std::endl;
        return nullptr;
    }

    for ( const Json::Value& locationIdJson : worldConfig["locations"] ) {
        std::string locationId = locationIdJson.asString();
        std::string locationPath = mapPath + "locations/" + locationId + "/";

        auto location = LocationFactory::createLocation( locationId, locationPath );

        if ( !location ) {
            std::cerr << "WorldFactory::createWorld failed to load location: " << locationId << std::endl;
            continue;
        }

        world->addLocation( std::move( location ) );
    }

    return world;
}

} // namespace Engine
