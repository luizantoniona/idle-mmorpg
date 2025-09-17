#include "WorldFactory.h"

#include <iostream>

#include <Helper/JsonHelper.h>

#include "RegionFactory.h"

namespace Core::Factory {

std::unique_ptr<Model::World> WorldFactory::createWorld( const std::string& mapPath ) {
    std::cout << "WorldFactory::createWorld" << std::endl;

    std::unique_ptr<Model::World> world = std::make_unique<Model::World>();

    Json::Value worldConfig = Helper::JsonHelper::loadJsonFile( mapPath + "world.json" );

    if ( !worldConfig.isMember( "regions" ) || !worldConfig[ "regions" ].isArray() ) {
        return nullptr;
    }

    for ( const Json::Value& regionNameJson : worldConfig[ "regions" ] ) {
        std::string regionName = regionNameJson.asString();
        std::string regionPath = mapPath + "world/" + regionName + "/";

        world->addRegion( std::move( RegionFactory::createRegion( regionName, regionPath ) ) );
    }

    return world;
}

} // namespace Core::Factory
