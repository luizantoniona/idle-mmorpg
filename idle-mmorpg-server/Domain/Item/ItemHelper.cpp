#include "ItemHelper.h"

#include <algorithm>
#include <array>
#include <string_view>

namespace Domain {

namespace {
constexpr std::array<std::pair<std::string_view, ItemType>, static_cast<int>( ItemType::UNKNOWN )> ITEM_TYPE_TABLE = { {
    { "CONSUMABLE", ItemType::CONSUMABLE },
    { "DIVERSE", ItemType::DIVERSE },
    { "EQUIPMENT", ItemType::EQUIPMENT },
    { "OFFHAND", ItemType::OFFHAND },
    { "TOOL", ItemType::TOOL },
    { "WEAPON", ItemType::WEAPON },
} };

constexpr std::array<std::pair<std::string_view, ItemCategory>, static_cast<int>( ItemCategory::UNKNOWN )> ITEM_CATEGORY_TABLE = { {
    { "FOOD", ItemCategory::FOOD },
    { "POTION", ItemCategory::POTION },
    { "MATERIAL", ItemCategory::MATERIAL },
    { "ORE", ItemCategory::ORE },
    { "HELMET", ItemCategory::HELMET },
    { "ARMOR", ItemCategory::ARMOR },
    { "LEG", ItemCategory::LEG },
    { "BOOT", ItemCategory::BOOT },
    { "AMULET", ItemCategory::AMULET },
    { "RING", ItemCategory::RING },
    { "SHIELD", ItemCategory::SHIELD },
    { "FISHINGROD", ItemCategory::FISHINGROD },
    { "SICKLE", ItemCategory::SICKLE },
    { "PICKAXE", ItemCategory::PICKAXE },
    { "WOODAXE", ItemCategory::WOODAXE },
    { "AXE", ItemCategory::AXE },
    { "DAGGER", ItemCategory::DAGGER },
    { "SWORD", ItemCategory::SWORD },
} };
} // namespace

ItemType ItemHelper::stringToType( const std::string& type ) {
    auto it = std::find_if( ITEM_TYPE_TABLE.begin(), ITEM_TYPE_TABLE.end(), [ & ]( const auto& pair ) {
        return pair.first == type;
    } );

    return it != ITEM_TYPE_TABLE.end() ? it->second : ItemType::UNKNOWN;
}

std::string ItemHelper::typeToString( ItemType type ) {
    auto it = std::find_if( ITEM_TYPE_TABLE.begin(), ITEM_TYPE_TABLE.end(), [ & ]( const auto& pair ) {
        return pair.second == type;
    } );

    return it != ITEM_TYPE_TABLE.end() ? std::string( it->first ) : "";
}

ItemCategory ItemHelper::stringToCategory( const std::string& category ) {
    auto it = std::find_if( ITEM_CATEGORY_TABLE.begin(), ITEM_CATEGORY_TABLE.end(), [ & ]( const auto& pair ) {
        return pair.first == category;
    } );

    return it != ITEM_CATEGORY_TABLE.end() ? it->second : ItemCategory::UNKNOWN;
}

std::string ItemHelper::categoryToString( ItemCategory category ) {
    auto it = std::find_if( ITEM_CATEGORY_TABLE.begin(), ITEM_CATEGORY_TABLE.end(), [ & ]( const auto& pair ) {
        return pair.second == category;
    } );

    return it != ITEM_CATEGORY_TABLE.end() ? std::string( it->first ) : "";
}

} // namespace Domain
