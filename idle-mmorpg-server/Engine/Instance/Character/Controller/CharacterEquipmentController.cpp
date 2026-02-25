#include "CharacterEquipmentController.h"

namespace Engine {

CharacterEquipmentController::CharacterEquipmentController( std::function<void( MessageSenderType, const Json::Value& )> sendMessage,
                                                            Domain::CharacterEquipment& equipment,
                                                            Manager::ItemManager& itemManager ) :
    CharacterController( sendMessage ),
    _equipment( equipment ),
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

    resolve( _equipment.helmet() );
    resolve( _equipment.armor() );
    resolve( _equipment.leg() );
    resolve( _equipment.boot() );
    resolve( _equipment.weapon() );
    resolve( _equipment.offhand() );
    resolve( _equipment.amulet() );
    resolve( _equipment.ring() );
    resolve( _equipment.pickaxe() );
    resolve( _equipment.woodaxe() );
    resolve( _equipment.fishingrod() );
    resolve( _equipment.sickle() );

    sendMessage( MessageSenderType::CHARACTER_EQUIPMENT, _equipment.toJson() );
}

void CharacterEquipmentController::onLeaveWorld() {
}

void CharacterEquipmentController::onTick() {
}

} // namespace Engine
