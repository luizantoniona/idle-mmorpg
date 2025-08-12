#include "CharacterInventory.h"

namespace {
constexpr const char* JSON_ITEMS = "items";
} // namespace

namespace Model {

CharacterInventory::CharacterInventory() {}

Json::Value CharacterInventory::toJson() {
    Json::Value root;
    for ( auto& item : items() ) {
        root[ JSON_ITEMS ].append( item.toJson() );
    }
    return root;
}

std::vector<CharacterInventoryItem>& CharacterInventory::items() {
    return _items;
}

void CharacterInventory::addItem( CharacterInventoryItem item ) {
    _items.push_back( item );
}

} // namespace Model
