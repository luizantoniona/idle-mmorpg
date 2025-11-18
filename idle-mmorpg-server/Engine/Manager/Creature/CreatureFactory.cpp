#include "CreatureFactory.h"

#include <iostream>

#include <Engine/Manager/Configuration/ServerImageManager.h>
#include <Shared/Commons/Singleton.h>
#include <Shared/Helper/JsonHelper.h>

namespace Engine {

std::unordered_map<std::string, std::unique_ptr<Domain::Creature> > CreatureFactory::createCreatures( const std::string& creaturesPath ) {
    std::cout << "CreatureFactory::createCreatures" << std::endl;

    std::unordered_map<std::string, std::unique_ptr<Domain::Creature> > creatures;

    Json::Value creaturesConfig = Helper::JsonHelper::loadJsonFile( creaturesPath + "creatures.json" );

    for ( const auto& typeEntry : creaturesConfig[ "types" ] ) {

        std::string type = typeEntry[ "type" ].asString();
        std::string typeDir = creaturesPath + "creatures/" + type + "/";

        for ( const auto& creatureId : typeEntry[ "creatures" ] ) {
            std::string id = creatureId.asString();
            std::string path = typeDir + id + ".json";

            std::unique_ptr<Domain::Creature> creature = createCreature( path );
            if ( creature ) {
                creature->setId( id );
                creature->setType( type );
                creatures[ id ] = std::move( creature );

            } else {
                std::cerr << "Failed to load creature: " << path << std::endl;
            }
        }
    }

    std::cout << "CreatureFactory::createCreatures Number of creatures loaded: " << creatures.size() << std::endl;

    return creatures;
}

std::unique_ptr<Domain::Creature> CreatureFactory::createCreature( const std::string& creaturePath ) {
    std::cout << "CreatureFactory::createCreature: " << creaturePath << std::endl;

    Json::Value creatureJson = Helper::JsonHelper::loadJsonFile( creaturePath );

    auto creature = std::make_unique<Domain::Creature>();
    creature->setName( creatureJson[ "name" ].asString() );
    creature->setDescription( creatureJson[ "description" ].asString() );

    creature->setIcon( creatureJson[ "icon" ].asString() );
    std::string baseDir = creaturePath.substr( 0, creaturePath.find_last_of( '/' ) + 1 );
    Commons::Singleton<Engine::ServerImageManager>::instance().loadImage( creature->icon(), baseDir + creature->icon() );

    creature->setExperience( creatureJson[ "experience" ].asInt() );
    creature->vitals().setMaxHealth( creatureJson[ "health" ].asDouble() );
    creature->vitals().setHealth( creatureJson[ "health" ].asDouble() );
    creature->vitals().setMaxMana( creatureJson[ "mana" ].asDouble() );
    creature->vitals().setMana( creatureJson[ "mana" ].asDouble() );
    creature->vitals().setMaxStamina( creatureJson[ "stamina" ].asDouble() );
    creature->vitals().setStamina( creatureJson[ "stamina" ].asDouble() );

    creature->setAttack( creatureJson[ "attack" ].asDouble() );
    creature->setAttackSpeed( creatureJson[ "attackSpeed" ].asDouble() );
    creature->setAccuracy( creatureJson[ "accuracy" ].asDouble() );

    creature->setDefense( creatureJson[ "defense" ].asDouble() );
    creature->setEvasion( creatureJson[ "evasion" ].asDouble() );

    for ( const auto& lootJson : creatureJson[ "loot" ] ) {
        Domain::CreatureLoot loot;
        loot.setId( lootJson[ "id" ].asString() );
        loot.setChance( lootJson[ "chance" ].asDouble() );
        loot.setMinAmount( lootJson[ "minAmount" ].asInt() );
        loot.setMaxAmount( lootJson[ "maxAmount" ].asInt() );

        creature->addLoot( loot );
    }

    return creature;
}

} // namespace Engine
