#include "CharacterInventoryController.h"

namespace Engine {

CharacterInventoryController::CharacterInventoryController( std::function<void( MessageSenderType, const Json::Value& )> sendMessage,
                                                            Domain::CharacterInventory& inventory,
                                                            Manager::ItemManager& itemManager ) :
    CharacterController( sendMessage ),
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

    sendMessage( MessageSenderType::CHARACTER_INVENTORY, _inventory.toJson() );
}

void CharacterInventoryController::onTickWorld() {
}

void CharacterInventoryController::onExitWorld() {
    for ( auto& item : _inventory.items() ) {
        item.setItem( nullptr );
    }
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
