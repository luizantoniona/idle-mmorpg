#ifndef CHARACTERINVENTORY_H
#define CHARACTERINVENTORY_H

#include <vector>

#include <json/json.h>

#include "CharacterInventoryItem.h"

namespace Model {

class CharacterInventory {
public:
    CharacterInventory();

    Json::Value toJson();

    std::vector<CharacterInventoryItem>& items();
    void addItem( CharacterInventoryItem item );

private:
    std::vector<CharacterInventoryItem> _items;
};

} // namespace Model

#endif // CHARACTERINVENTORY_H
