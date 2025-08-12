#include "ItemFactory.h"

#include <iostream>

#include <Commons/JsonHelper.h>

namespace Core::Factory {

std::unordered_map<std::string, std::unique_ptr<Model::Item> > ItemFactory::createItems( const std::string& itemsPath ) {
    std::cout << "ItemFactory::createItems" << std::endl;

    std::unordered_map<std::string, std::unique_ptr<Model::Item> > items;

    Json::Value itemsConfig = Commons::JsonHelper::loadJsonFile( itemsPath + "items.json" );

    for ( const auto& typeEntry : itemsConfig[ "types" ] ) {

        std::string type = typeEntry[ "type" ].asString();
        std::string typesPath = itemsPath + typeEntry[ "path" ].asString() + "/";
        Json::Value typesConfig = Commons::JsonHelper::loadJsonFile( typesPath + typeEntry[ "path" ].asString() + ".json" );

        for ( const auto& categoryEntry : typesConfig[ "categories" ] ) {

            std::string category = categoryEntry[ "category" ].asString();
            std::string categoryPath = categoryEntry[ "path" ].asString();
            std::string itemPath = typesPath + categoryPath;

            for ( const Json::Value& itemEntry : categoryEntry[ "items" ] ) {
                std::string itemId = itemEntry.asString();
                std::string itemFilePath = itemPath + "/" + itemId + ".json";

                auto item = createItem( itemFilePath );
                if ( item ) {
                    item->setId( itemId );
                    item->setType( type );
                    item->setCategory( category );
                    items[itemId] = std::move( item );

                } else {
                    std::cerr << "Failed to load item: " << itemId << " from " << itemFilePath << std::endl;
                }
            }
        }
    }

    std::cout << "ItemFactory::createItems Number of items loaded: " << items.size() << std::endl;

    return items;
}

std::unique_ptr<Model::Item> ItemFactory::createItem( const std::string& itemPath ) {
    std::cout << "ItemFactory::createItem: " << itemPath << std::endl;

    Json::Value itemJson = Commons::JsonHelper::loadJsonFile( itemPath );

    auto item = std::make_unique<Model::Item>();
    item->setName( itemJson[ "name" ].asString() );
    item->setDescription( itemJson[ "description" ].asString() );
    item->setRarity( itemJson[ "rarity" ].asString() );
    item->setValue( itemJson[ "value" ].asInt() );
    item->setIcon( itemJson[ "icon" ].asString() );

    if ( itemJson.isMember( "modifiers" ) && itemJson["modifiers"].isArray() ) {
        const Json::Value& modifiersJson = itemJson["modifiers"];
        std::vector<Model::ItemModifier> modifiers;

        for ( const auto& modifierJson : modifiersJson ) {
            Model::ItemModifier modifier;
            modifier.setType( modifierJson["type"].asString() );
            modifier.setTarget( modifierJson["target"].asString() );
            modifier.setValue( modifierJson["value"].asDouble() );

            modifiers.push_back( modifier );
        }

        item->setModifiers( modifiers );
    }

    return item;
}

} // namespace Core::Factory
