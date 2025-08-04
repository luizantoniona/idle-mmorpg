#include "CharacterInventory.h"

namespace Model {

CharacterInventory::CharacterInventory() {}

Json::Value CharacterInventory::toJson() {
    Json::Value root;

    //TODO: Implement inventary json when ready;

    return root;
}

std::vector<CharacterItem>& CharacterInventory::items() {
    return _items;
}

void CharacterInventory::addItem( CharacterItem item ) {
    _items.push_back( item );
}

} // namespace Model
