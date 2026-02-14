#ifndef CHARACTERINVENTORYCONTROLLER_H
#define CHARACTERINVENTORYCONTROLLER_H

#include <Domain/Character/CharacterInventory.h>
#include <Manager/Item/ItemManager.h>

#include "CharacterController.h"

namespace Engine {

class CharacterInventoryController : public CharacterController {
public:
    explicit CharacterInventoryController( Domain::CharacterInventory& inventory, Manager::ItemManager& itemManager );

    void onEnterWorld() override;
    void onTickWorld() override;
    void onExitWorld() override;

    bool addItem( const std::string& itemId, int amount );
    bool removeItem( const std::string& itemId, int amount );

private:
    Domain::CharacterInventory& _inventory;
    Manager::ItemManager& _itemManager;
};

} // namespace Engine

#endif // CHARACTERINVENTORYCONTROLLER_H
