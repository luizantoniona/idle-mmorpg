#include "LocationFactory.h"

#include <iostream>

#include <Commons/JsonHelper.h>

namespace System::Factory {

std::unique_ptr<Model::Location> LocationFactory::createLocation( const std::string& locationName, const std::string& locationPath ) {
    std::cout << "LocationFactory::createLocation Creating Location: " << locationName << std::endl;

    std::string locationJsonPath = locationPath + "/location.json";
    Json::Value locationJson = Commons::JsonHelper::loadJsonFile( locationJsonPath );
    auto location = std::make_unique<Model::Location>();

    if ( locationJson.isMember( "id" ) ) {
        location->setId( locationJson[ "id" ].asString() );
    }

    if ( locationJson.isMember( "name" ) ) {
        location->setName( locationJson[ "name" ].asString() );
    }

    if ( locationJson.isMember( "description" ) ) {
        location->setDescription( locationJson[ "description" ].asString() );
    }

    if ( locationJson.isMember( "coordinates" ) ) {
        Json::Value coordinatesJson = locationJson[ "coordinates" ];

        if ( coordinatesJson.isMember( "x" ) ) {
            location->setX( coordinatesJson[ "x" ].asInt() );
        }

        if ( coordinatesJson.isMember( "y" ) ) {
            location->setY( coordinatesJson[ "y" ].asInt() );
        }

        if ( coordinatesJson.isMember( "z" ) ) {
            location->setZ( coordinatesJson[ "z" ].asInt() );
        }
    }

    std::string actionsJsonPath = locationPath + "/actions.json";
    Json::Value actionsJson = Commons::JsonHelper::loadJsonFile( actionsJsonPath );
    for ( const Json::Value& actionJson : actionsJson[ "actions" ] ) {
        Model::LocationAction action;
        action.setId( actionJson[ "id" ].asString() );
        action.setLabel( actionJson[ "label" ].asString() );

        for ( const Json::Value& reqJson : actionJson[ "requirements" ] ) {
            Model::LocationActionRequirement requirement;

            // req.type = Core::Model::LocationActionRequirementModel::fromString( reqJson[ "type" ].asString() );
            // req.id = reqJson.get( "id", "" ).asString();
            // req.level = reqJson.get( "level", 0 ).asInt();
            // req.category = reqJson.get( "category", "" ).asString(); // ← substituindo subtype por category

            action.addRequirement( requirement );
        }

        location->addAction( action );
    }

    std::string enemiesJsonPath = locationPath + "/enemies.json";
    Json::Value enemiesJson = Commons::JsonHelper::loadJsonFile( enemiesJsonPath );

    return location;
}

std::unique_ptr<Model::LocationConnection> LocationFactory::createLocationConnection( const Json::Value& connectionJson ) {
    auto connection = std::make_unique<Model::LocationConnection>();

    connection->setOrigin( connectionJson[ "origin" ].asString() );
    connection->setDestination( connectionJson[ "destination" ].asString() );
    connection->setDirection( connectionJson[ "direction" ].asString() );

    return connection;
}

} // namespace System::Factory
