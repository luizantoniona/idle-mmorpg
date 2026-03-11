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

Domain::CharacterEquipmentItem* CharacterItemController::resolveSlot( const std::string& slot ) {
    if ( slot == "HELMET" ) {
        return &_characterEquipment.helmet();
    }
    if ( slot == "ARMOR" ) {
        return &_characterEquipment.armor();
    }
    if ( slot == "LEG" ) {
        return &_characterEquipment.leg();
    }
    if ( slot == "BOOT" ) {
        return &_characterEquipment.boot();
    }
    if ( slot == "WEAPON" ) {
        return &_characterEquipment.weapon();
    }
    if ( slot == "OFFHAND" ) {
        return &_characterEquipment.offhand();
    }
    if ( slot == "AMULET" ) {
        return &_characterEquipment.amulet();
    }
    if ( slot == "RING" ) {
        return &_characterEquipment.ring();
    }
    if ( slot == "PICKAXE" ) {
        return &_characterEquipment.pickaxe();
    }
    if ( slot == "WOODAXE" ) {
        return &_characterEquipment.woodaxe();
    }
    if ( slot == "FISHINGROD" ) {
        return &_characterEquipment.fishingrod();
    }
    if ( slot == "SICKLE" ) {
        return &_characterEquipment.sickle();
    } 

    return nullptr;
}

void CharacterItemController::handleEquip( const Json::Value& payload ) {
    std::string itemId = payload[ "item" ].asString();
    std::string slotId = payload[ "slot" ].asString();

    auto* equipmentSlot = resolveSlot( slotId );
    if ( !equipmentSlot ) {
        return;
    }

    if ( itemId.empty() ) {
        if ( !equipmentSlot->id().empty() ) {
            std::string oldItemId = equipmentSlot->id();

            _characterInventory.addItem( oldItemId, 1 );

            auto* inventoryItem = _characterInventory.itemById( oldItemId );
            if ( inventoryItem ) {

                const Domain::Item* item = _itemManager.itemById( oldItemId );
                if ( item ) {
                    inventoryItem->setItem( item );
                }
            }
        }

        equipmentSlot->setId( "" );
        equipmentSlot->setItem( nullptr );

    } else {
        auto* inventoryItem = _characterInventory.itemById( itemId );
        if ( !inventoryItem ) {
            return;
        }

        const Domain::Item* item = inventoryItem->item();
        if ( !item ) {
            return;
        }

        if ( equipmentSlot->id() == itemId ) {
            return;
        }

        if ( !equipmentSlot->id().empty() ) {
            _characterInventory.addItem( equipmentSlot->id(), 1 );
        }

        if ( !_characterInventory.removeItem( itemId, 1 ) ) {
            return;
        }

        equipmentSlot->setId( itemId );
        equipmentSlot->setItem( item );
    }

    _messageSender.sendMessage( MessageSenderType::CHARACTER_INVENTORY, _characterInventory.toJson() );

    _messageSender.sendMessage( MessageSenderType::CHARACTER_EQUIPMENT, _characterEquipment.toJson() );

    Json::Value eventPayload;
    _eventBus.publish( CharacterEvent( CharacterEventType::ITEM_EQUIPPED, eventPayload ) );
}

void CharacterItemController::handleUseItem( const Json::Value& payload ) {
    std::string itemId = payload[ "item" ].asString();

    auto* inventoryItem = _characterInventory.itemById( itemId );
    if ( !inventoryItem ) {
        return;
    }

    const Domain::Item* item = inventoryItem->item();
    if ( !item ) {
        return;
    }

    if ( item->type() != Domain::ItemType::CONSUMABLE ) {
        return;
    }

    for ( const Domain::ItemEffect& itemEffect : item->effects() ) {
        Domain::CharacterEffect effect;

        effect.setSource( itemId );
        effect.setSourceName( item->name() );
        effect.setType( itemEffect.type() );
        effect.setCategory( itemEffect.category() );
        effect.setValue( itemEffect.value() );
        effect.setDuration( itemEffect.duration() );
        effect.setCounter( 0 );

        Json::Value payload;
        payload[ "effect" ] = effect.toJson();
        _eventBus.publish( CharacterEvent( CharacterEventType::EFFECT_APPLY, payload ) );
    }

    _characterInventory.removeItem( itemId, 1 );

    _messageSender.sendMessage( MessageSenderType::CHARACTER_INVENTORY, _characterInventory.toJson() );
}

void CharacterItemController::onItemGained( const CharacterEvent& event ) {
    std::string itemId = event.payload()[ "item" ].asString();
    int amount = event.payload()[ "amount" ].asInt();

    if ( itemId == "coin_copper" ) {
        _characterWallet.setCopper( _characterWallet.copper() + amount );
        _messageSender.sendMessage( MessageSenderType::CHARACTER_WALLET, _characterWallet.toJson() );
        return;

    } else if ( itemId == "coin_silver" ) {
        _characterWallet.setSilver( _characterWallet.silver() + amount );
        _messageSender.sendMessage( MessageSenderType::CHARACTER_WALLET, _characterWallet.toJson() );
        return;

    } else if ( itemId == "coin_gold" ) {
        _characterWallet.setGold( _characterWallet.gold() + amount );
        _messageSender.sendMessage( MessageSenderType::CHARACTER_WALLET, _characterWallet.toJson() );
        return;
    }

    const Domain::Item* item = _itemManager.itemById( itemId );
    if ( !item ) {
        return;
    }

    _characterInventory.addItem( itemId, amount );

    auto* inventoryItem = _characterInventory.itemById( itemId );
    if ( inventoryItem ) {
        inventoryItem->setItem( item );
    }

    _messageSender.sendMessage( MessageSenderType::CHARACTER_INVENTORY, _characterInventory.toJson() );
}

} // namespace Engine
