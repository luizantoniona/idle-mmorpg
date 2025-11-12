#include "LocationFactory.h"

#include <iostream>

#include <Domain/Shared/RequirementHelper.h>
#include <Domain/World/Location/LocationAction.h>
#include <Domain/World/Location/LocationActionExperience.h>
#include <Engine/Manager/Creature/CreatureManager.h>
#include <Engine/Manager/Denizen/DenizenManager.h>
#include <Engine/Manager/Item/ItemManager.h>
#include <Engine/Manager/Configuration/ServerConfigurationManager.h>
#include <Shared/Commons/Singleton.h>
#include <Shared/Helper/JsonHelper.h>

namespace Engine {

std::unique_ptr<Domain::Location> LocationFactory::createLocation( const std::string& locationName, const std::string& locationPath ) {
    std::cout << "LocationFactory::createLocation Creating Location: " << locationName << std::endl;

    std::string locationJsonPath = locationPath + "/location.json";
    Json::Value locationJson = Helper::JsonHelper::loadJsonFile( locationJsonPath );

    auto location = std::make_unique<Domain::Location>();
    location->setId( locationJson[ "id" ].asString() );
    location->setName( locationJson[ "name" ].asString() );
    location->setDescription( locationJson[ "description" ].asString() );
    location->setTileSizeX( locationJson[ "sizeX" ].asInt() );
    location->setTileSizeY( locationJson[ "sizeY" ].asInt() );

    // --- Connections ---
    for ( const Json::Value& connectionJson : locationJson[ "connections" ] ) {
        Domain::LocationConnection connection;
        connection.setDestination( connectionJson[ "destination" ].asString() );
        connection.setStructure( connectionJson.get( "structure", "" ).asString() );
        connection.setLabel( connectionJson[ "label" ].asString() );
        connection.setX( connectionJson[ "x" ].asInt() );
        connection.setY( connectionJson[ "y" ].asInt() );

        for ( const Json::Value& reqJson : connectionJson[ "requirements" ] ) {
            Domain::Requirement requirement;
            requirement.setType( Helper::RequirementHelper::stringToEnum( reqJson[ "type" ].asString() ) );
            requirement.setId( reqJson[ "id" ].asString() );
            connection.addRequirement( requirement );
        }

        location->addConnection( connection );
    }

    // --- Structures ---
    for ( const Json::Value& structureJson : locationJson[ "structures" ] ) {
        Domain::LocationStructure structure;
        structure.setId( structureJson[ "id" ].asString() );
        structure.setLabel( structureJson[ "label" ].asString() );
        structure.setDescription( structureJson[ "description" ].asString() );
        structure.setX( structureJson[ "x" ].asInt() );
        structure.setY( structureJson[ "y" ].asInt() );
        location->addStructure( structure );
    }

    // --- Creatures ---
    for ( const Json::Value& creatureJson : locationJson[ "creatures" ] ) {
        Domain::LocationCreature creature;
        creature.setId( creatureJson[ "id" ].asString() );
        creature.setSpawnMin( creatureJson[ "min" ].asInt() );
        creature.setSpawnMax( creatureJson[ "max" ].asInt() );
        creature.setStructure( creatureJson.get( "structure", "" ).asString() );
        creature.setCreature( Commons::Singleton<Engine::CreatureManager>::instance().creatureById( creature.id() ) );
        location->addCreature( creature );
    }

    // --- Actions ---
    for ( const Json::Value& actionJson : locationJson[ "actions" ] ) {
        Domain::LocationAction action;
        action.setId( actionJson[ "id" ].asString() );
        action.setType( actionJson.get( "type", "" ).asString() );
        action.setLabel( actionJson[ "label" ].asString() );
        action.setStructure( actionJson.get( "structure", "" ).asString() );
        action.setDuration( actionJson.get( "duration", 0 ).asInt() * Commons::Singleton<Engine::ServerConfigurationManager>::instance().tickRate() );

        for ( const Json::Value& requirementJson : actionJson[ "requirements" ] ) {
            Domain::Requirement requirement;
            requirement.setType( Helper::RequirementHelper::stringToEnum( requirementJson[ "type" ].asString() ) );
            requirement.setId( requirementJson.get( "id", "" ).asString() );
            requirement.setAmount( requirementJson.get( "amount", 0 ).asInt() );
            action.addRequirement( requirement );
        }

        for ( const Json::Value& experienceJson : actionJson[ "experience" ] ) {
            Domain::LocationActionExperience experience;
            experience.setIdSkill( experienceJson[ "skill" ].asString() );
            experience.setAmount( experienceJson[ "amount" ].asInt() );
            action.addExperience( experience );
        }

        for ( const Json::Value& lootJson : actionJson[ "loot" ] ) {
            Domain::LocationActionLoot loot;
            loot.setId( lootJson[ "id" ].asString() );
            loot.setBaseAmount( lootJson.get( "baseAmount", 0.0 ).asDouble() );
            loot.setModifierAmount( lootJson.get( "modifierAmount", 0.0 ).asDouble() );
            loot.setBaseChance( lootJson.get( "baseChance", 0.0 ).asDouble() );
            loot.setModifierChance( lootJson.get( "modifierChance", 0.0 ).asDouble() );
            action.addLoot( loot );
        }

        location->addAction( action );
    }

    // --- Denizens ---
    for ( const Json::Value& denizenJson : locationJson["denizens"] ) {
        std::string denizenId = denizenJson["id"].asString();
        std::string structure = denizenJson.get( "structure", "" ).asString();

        Domain::Denizen* denizen = Commons::Singleton<Engine::DenizenManager>::instance().denizenById( denizenId );

        if ( !denizen ) {
            std::cerr << "Warning: Denizen with id '" << denizenId << "' not found in DenizenManager." << std::endl;
            continue;
        }

        denizen->setStructure( structure );

        location->addDenizen( denizen );
    }

    return location;
}

} // namespace Engine
