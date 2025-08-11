#include "LocationFactory.h"

#include <iostream>

#include <Commons/JsonHelper.h>
#include <Commons/Singleton.h>
#include <Core/Manager/CreatureManager.h>
#include <Model/World/Location/LocationAction.h>
#include <Model/World/Location/LocationActionExperience.h>
#include <Model/World/Location/LocationActionRequirement.h>

namespace Core::Factory {

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
        action.setStructure( actionJson.get( "structure", "" ).asString() );
        action.setDuration( actionJson[ "duration" ].asInt() );

        for ( const Json::Value& requirementJson : actionJson[ "requirements" ] ) {
            Model::LocationActionRequirement requirement;
            requirement.setId( requirementJson[ "id" ].asString() );
            requirement.setType( requirementJson[ "type" ].asString() );
            requirement.setCategory( requirementJson.get( "category", "" ).asString() );
            requirement.setLevel( requirementJson.get( "level", 0 ).asInt() );
            action.addRequirement( requirement );
        }

        for ( const Json::Value& experienceJson : actionJson[ "experience" ] ) {
            Model::LocationActionExperience experience;
            experience.setIdSkill( experienceJson[ "skill" ].asString() );
            experience.setAmount( experienceJson[ "amount" ].asInt() );
            action.addExperience( experience );
        }

        location->addAction( action );
    }

    std::string structuresJsonPath = locationPath + "/structures.json";
    Json::Value structuresJson = Commons::JsonHelper::loadJsonFile( structuresJsonPath );
    for ( const Json::Value& structureJson : structuresJson[ "structures" ] ) {
        Model::LocationStructure structure;
        structure.setId( structureJson["id"].asString() );
        structure.setLabel( structureJson["label"].asString() );
        structure.setDescription( structureJson["description"].asString() );

        location->addStructure( structure );
    }

    std::string creaturesJsonPath = locationPath + "/creatures.json";
    Json::Value creaturesJson = Commons::JsonHelper::loadJsonFile( creaturesJsonPath );
    for ( const Json::Value& creatureJson : creaturesJson[ "creatures" ] ) {
        Model::LocationCreature creature;
        creature.setId( creatureJson[ "id" ].asString() );
        creature.setSpawnMin( creatureJson[ "min" ].asInt() );
        creature.setSpawnMax( creatureJson[ "max" ].asInt() );
        creature.setStructure( creatureJson.get( "structure", "" ).asString() );
        creature.setCreature( Commons::Singleton<Manager::CreatureManager>::instance().creatureById( creature.id() ) );

        location->addCreature( creature );
    }

    return location;
}

std::unique_ptr<Model::LocationConnection> LocationFactory::createLocationConnection( const Json::Value& connectionJson ) {
    auto connection = std::make_unique<Model::LocationConnection>();

    connection->setOrigin( connectionJson[ "origin" ].asString() );
    connection->setDestination( connectionJson[ "destination" ].asString() );
    connection->setDirection( connectionJson[ "direction" ].asString() );

    return connection;
}

} // namespace Core::Factory
