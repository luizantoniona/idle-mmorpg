#include "CharacterInventory.h"

namespace Model {

CharacterInventory::CharacterInventory() {}

std::vector<CharacterItem>& CharacterInventory::items() {
    return _items;
}

void CharacterInventory::addItem( CharacterItem item ) {
    _items.push_back( item );
}

} // namespace Model
