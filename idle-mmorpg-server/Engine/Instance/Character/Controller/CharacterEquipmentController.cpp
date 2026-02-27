#include "CharacterEquipmentController.h"

namespace Engine {

CharacterEquipmentController::CharacterEquipmentController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                            Domain::Character& character,
                                                            Manager::ItemManager& itemManager ) :
    CharacterController( eventBus, messageSender ),
    _characterEquipment( character.equipment() ),
    _itemManager( itemManager ) {
}

void CharacterEquipmentController::onEnterWorld() {
    auto resolve = [ & ]( Domain::CharacterEquipmentItem& item ) {
        if ( item.id().empty() ) {
            return;
        }

        const Domain::Item* itemPointer = _itemManager.itemById( item.id() );
        if ( itemPointer ) {
            item.setItem( itemPointer );
        }
    };

    resolve( _characterEquipment.helmet() );
    resolve( _characterEquipment.armor() );
    resolve( _characterEquipment.leg() );
    resolve( _characterEquipment.boot() );
    resolve( _characterEquipment.weapon() );
    resolve( _characterEquipment.offhand() );
    resolve( _characterEquipment.amulet() );
    resolve( _characterEquipment.ring() );
    resolve( _characterEquipment.pickaxe() );
    resolve( _characterEquipment.woodaxe() );
    resolve( _characterEquipment.fishingrod() );
    resolve( _characterEquipment.sickle() );

    _messageSender.sendMessage( MessageSenderType::CHARACTER_EQUIPMENT, _characterEquipment.toJson() );
}

void CharacterEquipmentController::onLeaveWorld() {
}

void CharacterEquipmentController::onTick() {
}

} // namespace Engine
