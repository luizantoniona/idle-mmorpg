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

constexpr std::array<std::pair<std::string_view, ItemCategoryType>, static_cast<int>( ItemCategoryType::UNKNOWN )> ITEM_CATEGORY_TYPE_TABLE = { {
    { "FOOD", ItemCategoryType::FOOD },
    { "POTION", ItemCategoryType::POTION },
    { "MATERIAL", ItemCategoryType::MATERIAL },
    { "ORE", ItemCategoryType::ORE },
    { "HELMET", ItemCategoryType::HELMET },
    { "ARMOR", ItemCategoryType::ARMOR },
    { "LEG", ItemCategoryType::LEG },
    { "BOOT", ItemCategoryType::BOOT },
    { "AMULET", ItemCategoryType::AMULET },
    { "RING", ItemCategoryType::RING },
    { "SHIELD", ItemCategoryType::SHIELD },
    { "FISHINGROD", ItemCategoryType::FISHINGROD },
    { "SICKLE", ItemCategoryType::SICKLE },
    { "PICKAXE", ItemCategoryType::PICKAXE },
    { "WOODAXE", ItemCategoryType::WOODAXE },
    { "AXE", ItemCategoryType::AXE },
    { "DAGGER", ItemCategoryType::DAGGER },
    { "SWORD", ItemCategoryType::SWORD },
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

ItemCategoryType ItemHelper::stringToCategoryType( const std::string& type ) {
    auto it = std::find_if( ITEM_CATEGORY_TYPE_TABLE.begin(), ITEM_CATEGORY_TYPE_TABLE.end(), [ & ]( const auto& pair ) {
            return pair.first == type;
        } );

    return it != ITEM_CATEGORY_TYPE_TABLE.end() ? it->second : ItemCategoryType::UNKNOWN;
}

std::string ItemHelper::categoryTypeToString( ItemCategoryType type ) {
    auto it = std::find_if( ITEM_CATEGORY_TYPE_TABLE.begin(), ITEM_CATEGORY_TYPE_TABLE.end(), [ & ]( const auto& pair ) {
            return pair.second == type;
        } );

    return it != ITEM_CATEGORY_TYPE_TABLE.end() ? std::string( it->first ) : "";
}

} // namespace Domain
