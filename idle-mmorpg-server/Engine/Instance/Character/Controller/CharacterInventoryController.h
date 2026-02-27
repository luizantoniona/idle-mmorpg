#ifndef CHARACTERINVENTORYCONTROLLER_H
#define CHARACTERINVENTORYCONTROLLER_H

#include <Domain/Character/Character.h>
#include <Engine/Manager/Item/ItemManager.h>

#include "CharacterController.h"

namespace Engine {

class CharacterInventoryController : public CharacterController {
public:
    explicit CharacterInventoryController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                           Domain::Character& character,
                                           Manager::ItemManager& itemManager );

    void onEnterWorld() override;
    void onLeaveWorld() override;

    void onTick() override;

    bool addItem( const std::string& itemId, int amount );
    bool removeItem( const std::string& itemId, int amount );

private:
    Domain::CharacterInventory& _characterInventory;
    Manager::ItemManager& _itemManager;
};

} // namespace Engine

#endif // CHARACTERINVENTORYCONTROLLER_H
