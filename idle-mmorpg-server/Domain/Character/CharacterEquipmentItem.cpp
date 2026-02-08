#include "CharacterEquipmentItem.h"

namespace Domain {

CharacterEquipmentItem::CharacterEquipmentItem() :
    _id( "" ),
    _item( nullptr ) {
}

Json::Value CharacterEquipmentItem::toJson() {
    Json::Value root;
    if ( _item ) {
        root = item()->toJson();
    }
    return root;
}

std::string CharacterEquipmentItem::id() const {
    return _id;
}

void CharacterEquipmentItem::setId( const std::string& id ) {
    _id = id;
}

const Item* CharacterEquipmentItem::item() const {
    return _item;
}

void CharacterEquipmentItem::setItem( const Item* item ) {
    _item = item;
}

} // namespace Domain
