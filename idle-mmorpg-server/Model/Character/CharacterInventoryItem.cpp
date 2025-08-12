#include "CharacterInventoryItem.h"

namespace {
constexpr const char* JSON_ID = "id";
constexpr const char* JSON_AMOUNT = "amount";
} // namespace

namespace Model {

CharacterInventoryItem::CharacterInventoryItem() :
    _id( "" ),
    _amount( 0 ),
    _item( nullptr ) {
}

Json::Value CharacterInventoryItem::toJson() {
    Json::Value root;
    root[ JSON_ID ] = id();
    root[ JSON_AMOUNT ] = amount();

    if ( _item ) {
        Json::Value itemJson = item()->toJson();
        for ( const auto& key : itemJson.getMemberNames() ) {
            root[ key ] = itemJson[ key ];
        }
    }

    return root;
}

std::string CharacterInventoryItem::id() const {
    return _id;
}

void CharacterInventoryItem::setId( const std::string& id ) {
    _id = id;
}

int CharacterInventoryItem::amount() const {
    return _amount;
}

void CharacterInventoryItem::setAmount( int amount ) {
    _amount = amount;
}

const Item* CharacterInventoryItem::item() const {
    return _item;
}

void CharacterInventoryItem::setItem( const Item* item ) {
    _item = item;
}

} // namespace Model
