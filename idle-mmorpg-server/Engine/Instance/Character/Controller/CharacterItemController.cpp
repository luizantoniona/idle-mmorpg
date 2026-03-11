#include "CharacterItemController.h"

namespace Engine {

CharacterItemController::CharacterItemController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                  Domain::Character& character,
                                                  Manager::ItemManager& itemManager ) :
    CharacterController( eventBus, messageSender ),
    _characterEquipment( character.equipment() ),
    _characterInventory( character.inventory() ),
    _characterWallet( character.wallet() ),
    _itemManager( itemManager ) {

    _eventBus.subscribe( CharacterEventType::ITEM_GAINED, [ this ]( const CharacterEvent& event ) {
        onItemGained( event );
    } );
}

void CharacterItemController::onEnterWorld() {
    resolveInventory();
    resolveEquipment();

    _messageSender.sendMessage( MessageSenderType::CHARACTER_INVENTORY, _characterInventory.toJson() );

    _messageSender.sendMessage( MessageSenderType::CHARACTER_EQUIPMENT, _characterEquipment.toJson() );

    _messageSender.sendMessage( MessageSenderType::CHARACTER_WALLET, _characterWallet.toJson() );

    Json::Value payload;
    _eventBus.publish( CharacterEvent( CharacterEventType::ITEM_EQUIPPED, payload ) );
}

void CharacterItemController::onLeaveWorld() {
}

void CharacterItemController::onTick() {
}

void CharacterItemController::handleMessage( MessageReceiverType type, const Json::Value& payload ) {
    switch ( type ) {
    case MessageReceiverType::CHARACTER_ITEM_EQUIP:
        handleEquip( payload );
        break;

    case MessageReceiverType::CHARACTER_ITEM_USE:
        handleUseItem( payload );
        break;

    default:
        break;
    }
}

void CharacterItemController::resolveInventory() {
    for ( auto& item : _characterInventory.items() ) {
        resolveItem( item );
    }
}

void CharacterItemController::resolveItem( Domain::CharacterInventoryItem& item ) {
    if ( item.id().empty() ) {
        return;
    }

    const Domain::Item* itemPointer = _itemManager.itemById( item.id() );
    if ( !itemPointer ) {
        return;
    }

    item.setItem( itemPointer );
}

void CharacterItemController::resolveEquipment() {
    resolveItem( _characterEquipment.helmet() );
    resolveItem( _characterEquipment.armor() );
    resolveItem( _characterEquipment.leg() );
    resolveItem( _characterEquipment.boot() );
    resolveItem( _characterEquipment.weapon() );
    resolveItem( _characterEquipment.offhand() );
    resolveItem( _characterEquipment.amulet() );
    resolveItem( _characterEquipment.ring() );
    resolveItem( _characterEquipment.pickaxe() );
    resolveItem( _characterEquipment.woodaxe() );
    resolveItem( _characterEquipment.fishingrod() );
    resolveItem( _characterEquipment.sickle() );
}

void CharacterItemController::resolveItem( Domain::CharacterEquipmentItem& item ) {
    if ( item.id().empty() ) {
        return;
    }

    const Domain::Item* itemPointer = _itemManager.itemById( item.id() );
    if ( !itemPointer ) {
        return;
    }

    item.setItem( itemPointer );
}

void CharacterItemController::handleEquip( const Json::Value& payload ) {
    // TODO implement equip item

    Json::Value eventPayload;
    _eventBus.publish( CharacterEvent( CharacterEventType::ITEM_EQUIPPED, eventPayload ) );
}

void CharacterItemController::handleUseItem( const Json::Value& payload ) {
    // TODO implement use item

    Json::Value eventPayload;
    _eventBus.publish( CharacterEvent( CharacterEventType::ITEM_USED, eventPayload ) );
}

void CharacterItemController::onItemGained( const CharacterEvent& event ) {
    // TODO implement gained loot
    // Here we have to handle coins and wallet related things too
    /*
    Json::Value payload;
    payload[ "item" ] = itemId;
    payload[ "amount" ] = amount;

    receiverInstance->publishEvent( CharacterEventType::ITEM_GAINED, payload );
    */
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
