#include "CharacterInventoryController.h"

namespace Engine {

CharacterInventoryController::CharacterInventoryController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                            Domain::CharacterInventory& inventory,
                                                            Manager::ItemManager& itemManager ) :
    CharacterController( eventBus, messageSender ),
    _inventory( inventory ),
    _itemManager( itemManager ) {
}

void CharacterInventoryController::onEnterWorld() {
    for ( auto& item : _inventory.items() ) {
        const Domain::Item* itemPointer = _itemManager.itemById( item.id() );
        if ( !itemPointer ) {
            continue;
        }

        item.setItem( itemPointer );
    }

    _messageSender.sendMessage( MessageSenderType::CHARACTER_INVENTORY, _inventory.toJson() );
}

void CharacterInventoryController::onLeaveWorld() {
    for ( auto& item : _inventory.items() ) {
        item.setItem( nullptr );
    }
}

void CharacterInventoryController::onTick() {
}

bool CharacterInventoryController::addItem( const std::string& itemId, int amount ) {
    // TODO, ajustar quando precisar
    return true;
}

bool CharacterInventoryController::removeItem( const std::string& itemId, int amount ) {
    // TODO, ajustar quando precisar
    return true;
}

/*
bool CharacterInstance::addItemToInventory(
    const std::string& itemId,
    int amount
    ) {

 Item* item = itemManager.itemById( itemId );
 if ( !item ) {
     return false;
 }

 auto& inventory = _character->inventory();

 inventory.addItem( itemId, amount );

 auto* inventoryItem = inventory.itemById( itemId );
 if ( inventoryItem ) {
     inventoryItem->setItem( item );
 }

 return true;
}
*/

} // namespace Engine
