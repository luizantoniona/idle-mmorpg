#include "DenizenFactory.h"

#include <iostream>

#include <Domain/Shared/RequirementHelper.h>
#include <Engine/Manager/Configuration/ServerImageManager.h>
#include <Engine/Manager/Item/ItemManager.h>
#include <Engine/Manager/Quest/QuestManager.h>
#include <Shared/Commons/Singleton.h>
#include <Shared/Helper/JsonHelper.h>

namespace Engine {

std::unordered_map<std::string, std::unique_ptr<Domain::Denizen> > DenizenFactory::createDenizens( const std::string& denizensPath ) {
    std::cout << "DenizenFactory::createDenizens" << std::endl;

    std::unordered_map<std::string, std::unique_ptr<Domain::Denizen> > denizens;

    std::string denizensJsonPath = denizensPath + "denizens.json";
    Json::Value denizensJson = Helper::JsonHelper::loadJsonFile( denizensJsonPath );

    if ( !denizensJson.isMember( "denizens" ) || !denizensJson[ "denizens" ].isArray() ) {
        std::cerr << "DenizenFactory::createDenizens missing or invalid 'denizens' array at: " << denizensJsonPath << std::endl;
        return denizens;
    }

    for ( const Json::Value& denizenIdJson : denizensJson["denizens"] ) {
        std::string denizenId = denizenIdJson.asString();
        std::string denizenPath = denizensPath + "denizens/" + denizenId + ".json";

        std::unique_ptr<Domain::Denizen> denizen = createDenizen( denizenPath );
        if ( denizen ) {
            denizens[ denizenId ] = std::move( denizen );

        } else {
            std::cerr << "DenizenFactory::createDenizens failed to load denizen: " << denizenId << std::endl;
        }
    }

    std::cout << "DenizenFactory::createDenizens Number of denizens loaded: " << denizens.size() << std::endl;

    return denizens;
}

std::unique_ptr<Domain::Denizen> DenizenFactory::createDenizen( const std::string& denizenPath ) {
    std::cout << "DenizenFactory::createDenizen: " << denizenPath << std::endl;

    Json::Value denizenJson = Helper::JsonHelper::loadJsonFile( denizenPath );

    if ( denizenJson.isNull() ) {
        std::cerr << "DenizenFactory::createDenizen failed to load: " << denizenPath << std::endl;
        return nullptr;
    }

    auto denizen = std::make_unique<Domain::Denizen>();
    denizen->setId( denizenJson[ "id" ].asString() );
    denizen->setName( denizenJson[ "name" ].asString() );

    denizen->setIcon( denizenJson[ "icon" ].asString() );
    std::string baseDir = denizenPath.substr( 0, denizenPath.find_last_of( '/' ) + 1 );
    Commons::Singleton<Engine::ServerImageManager>::instance().loadImage( denizen->icon(), baseDir + denizen->icon() );

    // --- Quests ---
    for ( const Json::Value& questJson : denizenJson[ "quests" ] ) {
        auto quest = std::make_unique<Domain::Quest>();
        quest->setId( questJson[ "id" ].asString() );
        quest->setDenizenId( denizen->id() );
        quest->setTitle( questJson[ "title" ].asString() );
        quest->setDescription( questJson[ "description" ].asString() );
        quest->setType( questJson[ "type" ].asString() );
        quest->setObjectiveId( questJson[ "objectiveId" ].asString() );
        quest->setAmount( questJson[ "amount" ].asInt() );

        for ( const Json::Value& requirementJson : questJson[ "requirements" ] ) {
            Domain::Requirement requirement;
            requirement.setType( Helper::RequirementHelper::stringToEnum( requirementJson[ "type" ].asString() ) );
            requirement.setId( requirementJson[ "id" ].asString() );
            requirement.setAmount( requirementJson.get( "amount", 0 ).asInt() );
            quest->addRequirement( requirement );
        }

        for ( const Json::Value& rewardJson : questJson[ "rewards" ] ) {
            Domain::QuestReward reward;
            reward.setType( rewardJson[ "type" ].asString() );
            reward.setId( rewardJson[ "id" ].asString() );
            reward.setAmount( rewardJson.get( "amount", 0 ).asInt() );
            quest->addReward( reward );
        }

        std::string questId = quest->id();
        Commons::Singleton<Engine::QuestManager>::instance().addQuest( std::move( quest ) );
        const Domain::Quest* questPtr = Commons::Singleton<Engine::QuestManager>::instance().questById( questId );

        Domain::DenizenQuest denizenQuest;
        denizenQuest.setId( questId );
        denizenQuest.setQuest( questPtr );
        denizen->addQuest( denizenQuest );
    }

    // --- Trade ---
    Domain::DenizenTrade trade;
    for ( const Json::Value& sellItem : denizenJson[ "sell" ] ) {
        Domain::DenizenTradeItem item;
        item.setId( sellItem.asString() );
        item.setItem( Commons::Singleton<Engine::ItemManager>::instance().itemById( item.id() ) );
        trade.addSellItem( item );
    }

    for ( const Json::Value& buyItem : denizenJson[ "buy" ] ) {
        Domain::DenizenTradeItem item;
        item.setId( buyItem.asString() );
        item.setItem( Commons::Singleton<Engine::ItemManager>::instance().itemById( item.id() ) );
        trade.addBuyItem( item );
    }

    denizen->setTrade( trade );

    std::cout << "DenizenFactory::createDenizen Loaded: " << denizen->name()
              << " Quests:" << denizen->quests().size()
              << " Sells:" << trade.sellItems().size()
              << " Buy:" << trade.buyItems().size() << std::endl;

    return denizen;
}

} // namespace Engine
