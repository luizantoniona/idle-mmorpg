#include "ItemFactory.h"

#include <iostream>

#include <Domain/Item/ItemHelper.h>
#include <Engine/Manager/Server/ServerConfigurationManager.h>
#include <Engine/Manager/Server/ServerImageManager.h>
#include <Shared/Commons/Singleton.h>
#include <Shared/Helper/JsonHelper.h>

namespace Manager {

std::unordered_map<std::string, std::unique_ptr<Domain::Item> > ItemFactory::createItems( const std::string& itemsPath ) {
    std::cout << "ItemFactory::createItems" << std::endl;

    std::unordered_map<std::string, std::unique_ptr<Domain::Item> > items;

    Json::Value itemsConfig = Helper::JsonHelper::loadJsonFile( itemsPath + "items.json" );

    for ( const auto& itemEntry : itemsConfig[ "items" ] ) {
        std::string itemFilePath = itemsPath + itemEntry.asString() + ".json";

        auto item = createItem( itemFilePath );
        if ( item ) {
            items[ item->id() ] = std::move( item );

        } else {
            std::cerr << "Failed to load item: " << itemFilePath << std::endl;
        }
    }

    std::cout << "ItemFactory::createItems Number of items loaded: " << items.size() << std::endl;

    return items;
}

std::unique_ptr<Domain::Item> ItemFactory::createItem( const std::string& itemPath ) {
    std::cout << "ItemFactory::createItem: " << itemPath << std::endl;

    Json::Value itemJson = Helper::JsonHelper::loadJsonFile( itemPath );

    const Domain::ItemType itemType = Domain::ItemHelper::stringToType( itemJson[ "type" ].asString() );
    const Domain::ItemCategory itemCategory = Domain::ItemHelper::stringToCategory( itemJson[ "category" ].asString() );

    if ( itemType == Domain::ItemType::UNKNOWN || itemCategory == Domain::ItemCategory::UNKNOWN ) {
        std::cout << "Item Type not mapped: " << itemJson[ "type" ].asString() << " or Category: " << itemJson[ "category" ].asString() << std::endl;
        return nullptr;
    }

    auto item = std::make_unique<Domain::Item>();
    item->setId( itemJson[ "id" ].asString() );
    item->setType( itemType );
    item->setCategory( itemCategory );
    item->setName( itemJson[ "name" ].asString() );
    item->setDescription( itemJson[ "description" ].asString() );
    item->setPrice( itemJson[ "price" ].asInt() );

    item->setIcon( itemJson[ "icon" ].asString() );
    std::string baseDir = itemPath.substr( 0, itemPath.find_last_of( '/' ) + 1 );
    Commons::Singleton<Manager::ServerImageManager>::instance().loadImage( item->icon(), baseDir + item->icon() );

    if ( itemJson.isMember( "combat" ) && itemJson[ "combat" ].isObject() ) {
        const Json::Value& combatJson = itemJson[ "combat" ];
        Domain::ItemCombat combat;
        combat.setAttack( combatJson[ "attack" ].asDouble() );
        combat.setAttackSpeed( combatJson[ "attackSpeed" ].asDouble() );
        combat.setDefense( combatJson[ "defense" ].asDouble() );
        item->setCombat( combat );
    }

    if ( itemJson.isMember( "bonus" ) && itemJson[ "bonus" ].isArray() ) {
        const Json::Value& bonusesJson = itemJson[ "bonus" ];
        std::vector<Domain::ItemBonus> bonuses;

        for ( const auto& bonusJson : bonusesJson ) {
            Domain::ItemBonus bonus;
            bonus.setType( bonusJson[ "type" ].asString() );
            bonus.setCategory( bonusJson[ "category" ].asString() );
            bonus.setValue( bonusJson[ "value" ].asDouble() );

            bonuses.push_back( bonus );
        }

        item->setBonuses( bonuses );
    }

    if ( itemJson.isMember( "effects" ) && itemJson[ "effects" ].isArray() ) {
        const Json::Value& effectsJson = itemJson[ "effects" ];
        std::vector<Domain::ItemEffect> effects;

        for ( const auto& effectJson : effectsJson ) {
            Domain::ItemEffect effect;
            effect.setType( effectJson[ "type" ].asString() );
            effect.setCategory( effectJson[ "category" ].asString() );
            effect.setValue( effectJson[ "value" ].asDouble() );
            effect.setDuration( effectJson[ "duration" ].asInt() * Commons::Singleton<Manager::ServerConfigurationManager>::instance().tickRate() );

            effects.push_back( effect );
        }

        item->setEffects( effects );
    }

    return item;
}

} // namespace Manager
