#include "WorldFactory.h"

#include <iostream>

#include <Commons/JsonHelper.h>

#include "RegionFactory.h"

namespace System::Factory {

std::unique_ptr<Model::World> WorldFactory::createWorld( const std::string& mapPath ) {
    std::cout << "WorldFactory::createWorld" << std::endl;

    std::unique_ptr<Model::World> world = std::make_unique<Model::World>();

    Json::Value worldConfig = Commons::JsonHelper::loadJsonFile( mapPath + "world.json" );

    if ( !worldConfig.isMember( "regions" ) || !worldConfig[ "regions" ].isArray() ) {
        return nullptr;
    }

    for ( const Json::Value& regionNameJson : worldConfig[ "regions" ] ) {
        std::string regionName = regionNameJson.asString();
        std::string regionPath = mapPath + "world/" + regionName + "/";

        world->addRegion( std::move( RegionFactory::createRegion( regionName, regionPath ) ) );
    }

    for ( const Json::Value& regionConnectionJson : worldConfig["connections"] ) {
        if ( !regionConnectionJson.isMember( "origin" ) || !regionConnectionJson.isMember( "destination" ) ) {
            continue;
        }

        world->addConnection( std::move( RegionFactory::createRegionConnection( regionConnectionJson ) ) );
    }

    return world;
}

} // namespace System::Factory
