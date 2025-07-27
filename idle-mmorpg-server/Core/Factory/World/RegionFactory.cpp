#include "RegionFactory.h"

#include <iostream>

#include <Commons/JsonHelper.h>

#include "LocationFactory.h"

namespace Core::Factory {

std::unique_ptr<Model::Region> RegionFactory::createRegion( const std::string& regionName, const std::string& regionPath ) {
    std::cout << "RegionFactory::createRegion Creating Region: " << regionName << std::endl;

    auto region = std::make_unique<Model::Region>();
    region->setId( regionName );

    Json::Value regionConfig = Commons::JsonHelper::loadJsonFile( regionPath + "region.json" );

    if ( regionConfig.isMember( "name" ) ) {
        region->setName( regionConfig["name"].asString() );
    }

    if ( regionConfig.isMember( "description" ) ) {
        region->setDescription( regionConfig["description"].asString() );
    }

    for ( const Json::Value& locationIdJson : regionConfig["locations"] ) {
        std::string locationId = locationIdJson.asString();
        std::string locationPath = regionPath + "areas/" + locationId;

        region->addLocation( std::move( LocationFactory::createLocation( locationId, locationPath ) ) );
    }

    for ( const Json::Value& connectionJson : regionConfig["connections"] ) {
        if ( !connectionJson.isMember( "origin" ) || !connectionJson.isMember( "destination" ) ) {
            continue;
        }

        region->addConnection( std::move( LocationFactory::createLocationConnection( connectionJson ) ) );
    }

    return region;
}

std::unique_ptr<Model::RegionConnection> RegionFactory::createRegionConnection( const Json::Value& connectionJson ) {
    auto connection = std::make_unique<Model::RegionConnection>();

    connection->setOrigin( connectionJson["origin"].asString() );
    connection->setDestination( connectionJson["destination"].asString() );

    return connection;
}

} // namespace Core::Factory
