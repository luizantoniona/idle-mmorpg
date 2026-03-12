#include "ItemFactory.h"

#include <iostream>

#include <Domain/Item/ItemHelper.h>
#include <Domain/Skill/SkillHelper.h>
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
    const Domain::ItemCategoryType itemCategory = Domain::ItemHelper::stringToCategoryType( itemJson[ "category" ].asString() );

    if ( itemType == Domain::ItemType::UNKNOWN || itemCategory == Domain::ItemCategoryType::UNKNOWN ) {
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

    // --- ItemBonus ---
    const auto& bonusJson = itemJson[ "bonus" ];
    if ( !bonusJson.isNull() ) {
        Domain::ItemBonus bonus;
        bonus.setType( Domain::SkillHelper::stringToType( bonusJson[ "skill" ].asString() ) );
        bonus.setValue( bonusJson[ "value" ].asDouble() );

        item->setBonus( bonus );
    }

    // --- ItemCombat ---
    const auto& combatJson = itemJson[ "combat" ];
    if ( !combatJson.isNull() ) {
        Domain::ItemCombat combat;
        combat.setAttack( combatJson[ "attack" ].asDouble() );
        combat.setDefense( combatJson[ "defense" ].asDouble() );
        item->setCombat( combat );
    }

    // --- ItemEffect ---
    const auto& effectJson = itemJson[ "effects" ];
    if ( !effectJson.isNull() ) {
        Domain::ItemEffect effect;
        effect.setHealth( effectJson[ "health" ].asDouble() );
        effect.setMana( effectJson[ "mana" ].asDouble() );
        effect.setStamina( effectJson[ "stamina" ].asDouble() );
        effect.setDuration( effectJson[ "duration" ].asInt() * Commons::Singleton<Manager::ServerConfigurationManager>::instance().tickRate() );

        item->setEffect( effect );
    }

    return item;
}

} // namespace Manager
