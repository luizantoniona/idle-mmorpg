#ifndef CHARACTERINVENTORY_H
#define CHARACTERINVENTORY_H

#include <vector>

#include <Model/Character/CharacterItem.h>

namespace Model {

class CharacterInventory {
public:
    CharacterInventory();

    std::vector<CharacterItem>& items();
    void addItem( CharacterItem item );

private:
    std::vector<CharacterItem> _items;
};

} // namespace Model

#endif // CHARACTERINVENTORY_H
