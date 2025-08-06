#include "CharacterEquipmentItem.h"

namespace {
constexpr const char* JSON_ID = "id";
constexpr const char* JSON_ITEM = "item";
} // namespace

namespace Model {

CharacterEquipmentItem::CharacterEquipmentItem() :
    _id( "" ),
    _item( nullptr ) {
}

Json::Value CharacterEquipmentItem::toJson() {
    Json::Value root;
    root[ JSON_ID ] = id();

    if ( _item ) {
        root[ JSON_ITEM ] = item()->toJson();
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

} // namespace Model
