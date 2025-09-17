#include "ItemFactory.h"

#include <iostream>

#include <Commons/Singleton.h>
#include <Core/Manager/ServerConfigurationManager.h>
#include <Helper/JsonHelper.h>

namespace Core::Factory {

std::unordered_map<std::string, std::unique_ptr<Model::Item> > ItemFactory::createItems( const std::string& itemsPath ) {
    std::cout << "ItemFactory::createItems" << std::endl;

    std::unordered_map<std::string, std::unique_ptr<Model::Item> > items;

    Json::Value itemsConfig = Helper::JsonHelper::loadJsonFile( itemsPath + "items.json" );

    for ( const auto& itemEntry : itemsConfig[ "items" ] ) {
        std::string itemFilePath = itemsPath + itemEntry.asString() + ".json";

        auto item = createItem( itemFilePath );
        if ( item ) {
            items[item->id()] = std::move( item );

        } else {
            std::cerr << "Failed to load item: " << itemFilePath << std::endl;
        }
    }

    std::cout << "ItemFactory::createItems Number of items loaded: " << items.size() << std::endl;

    return items;
}

std::unique_ptr<Model::Item> ItemFactory::createItem( const std::string& itemPath ) {
    std::cout << "ItemFactory::createItem: " << itemPath << std::endl;

    Json::Value itemJson = Helper::JsonHelper::loadJsonFile( itemPath );

    auto item = std::make_unique<Model::Item>();
    item->setId( itemJson[ "id" ].asString() );
    item->setType( itemJson[ "type" ].asString() );
    item->setCategory( itemJson[ "category" ].asString() );
    item->setName( itemJson[ "name" ].asString() );
    item->setDescription( itemJson[ "description" ].asString() );
    item->setRarity( itemJson[ "rarity" ].asString() );
    item->setPrice( itemJson[ "price" ].asInt() );
    item->setIcon( itemJson[ "icon" ].asString() );

    if ( itemJson.isMember( "bonus" ) && itemJson[ "bonus" ].isArray() ) {
        const Json::Value& bonusesJson = itemJson[ "bonus" ];
        std::vector<Model::ItemBonus> bonuses;

        for ( const auto& bonusJson : bonusesJson ) {
            Model::ItemBonus bonus;
            bonus.setType( bonusJson[ "type" ].asString() );
            bonus.setCategory( bonusJson[ "category" ].asString() );
            bonus.setValue( bonusJson[ "value" ].asDouble() );

            bonuses.push_back( bonus );
        }

        item->setBonuses( bonuses );
    }

    if ( itemJson.isMember( "effects" ) && itemJson[ "effects" ].isArray() ) {
        const Json::Value& effectsJson = itemJson[ "effects" ];
        std::vector<Model::ItemEffect> effects;

        for ( const auto& effectJson : effectsJson ) {
            Model::ItemEffect effect;
            effect.setType( effectJson[ "type" ].asString() );
            effect.setCategory( effectJson[ "category" ].asString() );
            effect.setValue( effectJson[ "value" ].asDouble() );
            effect.setDuration( effectJson[ "duration" ].asInt() * Commons::Singleton<Core::Manager::ServerConfigurationManager>::instance().tickRate() );

            effects.push_back( effect );
        }

        item->setEffects( effects );
    }

    return item;
}

} // namespace Core::Factory
