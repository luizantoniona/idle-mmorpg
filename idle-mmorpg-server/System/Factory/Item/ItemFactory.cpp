#include "ItemFactory.h"

#include <iostream>

#include <Commons/JsonHelper.h>
#include <Model/Item/Item.h>

namespace System::Factory {

std::unordered_map<std::string, std::unique_ptr<Model::Item> > ItemFactory::createItems( const std::string& itemsPath ) {
    std::cout << "ItemFactory::createItems" << std::endl;

    const std::string basePath = itemsPath;

    Json::Value itemsConfig = Commons::JsonHelper::loadJsonFile( basePath + "items.json" );

    std::unordered_map<std::string, std::unique_ptr<Model::Item> > items;

    // for ( const auto& itemEntry : itemsConfig[ "items" ] ) {
    //     std::string id = itemEntry[ "id" ].asString();
    //     std::string relativePath = itemEntry[ "path" ].asString();
    //     std::string fullPath = itemsPath + relativePath;

    //     auto item = createItem( fullPath );
    //     if ( item ) {
    //         item->setId( id );
    //         items[ id ] = std::move( item );
    //     }
    // }

    return items;
}

std::unique_ptr<Model::Item> ItemFactory::createItem( const std::string& itemPath ) {
    std::cout << "ItemFactory::createItem: " << itemPath << std::endl;

    Json::Value itemJson = Commons::JsonHelper::loadJsonFile( itemPath );

    auto item = std::make_unique<Model::Item>();
    item->setName( itemJson[ "name" ].asString() );
    item->setDescription( itemJson[ "description" ].asString() );
    item->setType( itemJson[ "type" ].asString() );
    item->setCategory( itemJson[ "category" ].asString() );
    item->setRarity( itemJson[ "rarity" ].asString() );
    item->setValue( itemJson[ "value" ].asInt() );
    item->setIcon( itemJson[ "icon" ].asString() );

    // std::map<std::string, double> attributes;
    // for ( const auto& key : itemJson[ "attributes" ].getMemberNames() ) {
    //     attributes[ key ] = itemJson[ "attributes" ][ key ].asDouble();
    // }
    // item->setAttributes( attributes );

    return item;
}

} // namespace System::Factory
