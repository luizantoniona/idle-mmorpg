#include "LocationFactory.h"

#include <iostream>

#include <Commons/JsonHelper.h>
#include <Commons/Singleton.h>
#include <Core/Manager/CreatureManager.h>
#include <Core/Manager/ItemManager.h>
#include <Core/Manager/QuestManager.h>
#include <Core/Manager/ServerConfigurationManager.h>
#include <Model/World/Location/LocationAction.h>
#include <Model/World/Location/LocationActionExperience.h>
#include <Model/World/Location/LocationActionRequirement.h>

namespace Core::Factory {

std::unique_ptr<Model::Location> LocationFactory::createLocation( const std::string& locationName, const std::string& locationPath ) {
    std::cout << "LocationFactory::createLocation Creating Location: " << locationName << std::endl;

    std::string locationJsonPath = locationPath + "/location.json";
    Json::Value locationJson = Commons::JsonHelper::loadJsonFile( locationJsonPath );
    auto location = std::make_unique<Model::Location>();

    location->setId( locationJson[ "id" ].asString() );
    location->setName( locationJson[ "name" ].asString() );
    location->setDescription( locationJson[ "description" ].asString() );
    location->setTileSizeX( locationJson[ "sizeX" ].asInt() );
    location->setTileSizeY( locationJson[ "sizeY" ].asInt() );

    Json::Value connectionsJson = locationJson[ "connections" ];
    for ( const Json::Value& connectionJson : connectionsJson ) {
        Model::LocationConnection connection;
        connection.setDestination( connectionJson[ "destination" ].asString() );
        connection.setStructure( connectionJson[ "structure" ].asString() );
        connection.setLabel( connectionJson[ "label" ].asString() );
        connection.setX( connectionJson[ "x" ].asInt() );
        connection.setY( connectionJson[ "y" ].asInt() );

        Json::Value requirementsJson = connectionJson["requirements"];
        for ( const Json::Value& reqJson : requirementsJson ) {
            Model::LocationConnectionRequirement requirement;
            requirement.setType( reqJson[ "type" ].asString() );
            requirement.setId( reqJson[ "id" ].asString() );
            connection.addRequirement( requirement );
        }

        location->addConnection( connection );
    }

    std::string actionsJsonPath = locationPath + "/actions.json";
    Json::Value actionsJson = Commons::JsonHelper::loadJsonFile( actionsJsonPath );
    for ( const Json::Value& actionJson : actionsJson[ "actions" ] ) {
        Model::LocationAction action;
        action.setId( actionJson[ "id" ].asString() );
        action.setType( actionJson[ "type" ].asString() );
        action.setLabel( actionJson[ "label" ].asString() );
        action.setStructure( actionJson.get( "structure", "" ).asString() );
        action.setDuration( actionJson[ "duration" ].asInt() * Commons::Singleton<Core::Manager::ServerConfigurationManager>::instance().tickRate() );

        for ( const Json::Value& requirementJson : actionJson[ "requirements" ] ) {
            Model::LocationActionRequirement requirement;
            requirement.setId( requirementJson[ "id" ].asString() );
            requirement.setType( requirementJson[ "type" ].asString() );
            requirement.setAmount( requirementJson[ "amount" ].asInt() );
            action.addRequirement( requirement );
        }

        for ( const Json::Value& experienceJson : actionJson[ "experience" ] ) {
            Model::LocationActionExperience experience;
            experience.setIdSkill( experienceJson[ "skill" ].asString() );
            experience.setAmount( experienceJson[ "amount" ].asInt() );
            action.addExperience( experience );
        }

        for ( const Json::Value& lootJson : actionJson[ "loot" ] ) {
            Model::LocationActionLoot loot;
            loot.setId( lootJson[ "id" ].asString() );
            loot.setBaseAmount( lootJson[ "baseAmount" ].asDouble() );
            loot.setModifierAmount( lootJson[ "modifierAmount" ].asDouble() );
            loot.setBaseChance( lootJson[ "baseChance" ].asDouble() );
            loot.setModifierChance( lootJson[ "modifierChance" ].asDouble() );
            action.addLoot( loot );
        }

        location->addAction( action );
    }

    std::string structuresJsonPath = locationPath + "/structures.json";
    Json::Value structuresJson = Commons::JsonHelper::loadJsonFile( structuresJsonPath );
    for ( const Json::Value& structureJson : structuresJson[ "structures" ] ) {
        Model::LocationStructure structure;
        structure.setId( structureJson[ "id" ].asString() );
        structure.setLabel( structureJson[ "label" ].asString() );
        structure.setDescription( structureJson[ "description" ].asString() );
        structure.setX( structureJson[ "x" ].asInt() );
        structure.setY( structureJson[ "y" ].asInt() );

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

    std::string denizensJsonPath = locationPath + "/denizens.json";
    Json::Value denizensJson = Commons::JsonHelper::loadJsonFile( denizensJsonPath );
    for ( const Json::Value& denizenJson : denizensJson[ "denizens" ] ) {
        Model::Denizen denizen;
        denizen.setId( denizenJson[ "id" ].asString() );
        denizen.setName( denizenJson[ "name" ].asString() );
        denizen.setStructure( denizenJson.get( "structure", "" ).asString() );
        denizen.setIcon( denizenJson.get( "icon", "" ).asString() );

        // for ( const Json::Value& dialogueJson : denizenJson[ "dialogues" ] ) {
        //     Model::DenizenDialogue dialogue;
        //     dialogue.setOption( dialogueJson[ "option" ].asString() );
        //     for ( const Json::Value& line : dialogueJson[ "lines" ] ) {
        //         dialogue.addLine( line.asString() );
        //     }
        //     denizen.addDialogue( dialogue );
        // }

        for ( const Json::Value& questJson : denizenJson[ "quests" ] ) {
            auto quest = std::make_unique<Model::Quest>();
            quest->setId( questJson[ "id" ].asString() );
            quest->setDenizenId( denizen.id() );
            quest->setTitle( questJson[ "title" ].asString() );
            quest->setDescription( questJson[ "description" ].asString() );
            quest->setType( questJson[ "type" ].asString() );
            quest->setObjectiveId( questJson[ "objectiveId" ].asString() );
            quest->setAmount( questJson[ "amount" ].asInt() );

            for ( const Json::Value& requirementJson : questJson[ "requirements" ] ) {
                Model::QuestRequirement requirement;
                requirement.setType( requirementJson[ "type" ].asString() );
                requirement.setId( requirementJson[ "id" ].asString() );
                requirement.setAmount( requirementJson.get( "amount", 0 ).asInt() );
                quest->addRequirement( requirement );
            }

            for ( const Json::Value& rewardJson : questJson[ "rewards" ] ) {
                Model::QuestReward reward;
                reward.setType( rewardJson[ "type" ].asString() );
                reward.setId( rewardJson[ "id" ].asString() );
                reward.setAmount( rewardJson.get( "amount", 0 ).asInt() );
                quest->addReward( reward );
            }

            std::string questId = quest->id();

            Commons::Singleton<Core::Manager::QuestManager>::instance().addQuest( std::move( quest ) );
            const Model::Quest* questPtr = Commons::Singleton<Core::Manager::QuestManager>::instance().questById( questId );

            Model::DenizenQuest denizenQuest;
            denizenQuest.setId( questId );
            denizenQuest.setQuest( questPtr );

            denizen.addQuest( denizenQuest );
        }

        std::cout << "LocationFactory::createLocation Denizen: " << denizen.name() << " Quests: " << denizen.quests().size() << std::endl;

        Model::DenizenTrade trade;
        for ( const Json::Value& sellItem : denizenJson[ "sell" ] ) {
            Model::DenizenTradeItem item;
            item.setId( sellItem.asString() );
            item.setItem( Commons::Singleton<Manager::ItemManager>::instance().itemById( item.id() ) );
            trade.addSellItem( item );
        }

        for ( const Json::Value& buyItem : denizenJson[ "buy" ] ) {
            Model::DenizenTradeItem item;
            item.setId( buyItem.asString() );
            item.setItem( Commons::Singleton<Manager::ItemManager>::instance().itemById( item.id() ) );
            trade.addBuyItem( item );
        }

        denizen.setTrade( trade );

        location->addDenizen( denizen );
    }

    return location;
}

} // namespace Core::Factory
