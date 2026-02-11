#ifndef CHARACTERINVENTORYCONTROLLER_H
#define CHARACTERINVENTORYCONTROLLER_H

#include <Domain/Character/CharacterInventory.h>
#include <Manager/Item/ItemManager.h>

namespace Engine {

class CharacterInventoryController {
public:
    explicit CharacterInventoryController( Domain::CharacterInventory& inventory, Manager::ItemManager& itemManager );

    void onEnterWorld();
    void onExitWorld();

    bool addItem( const std::string& itemId, int amount );
    bool removeItem( const std::string& itemId, int amount );

private:
    Domain::CharacterInventory& _inventory;
    Manager::ItemManager& _itemManager;
};

} // namespace Engine

#endif // CHARACTERINVENTORYCONTROLLER_H
