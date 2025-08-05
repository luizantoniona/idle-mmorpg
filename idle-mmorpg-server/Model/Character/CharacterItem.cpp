#include "CharacterItem.h"

namespace Model {

CharacterItem::CharacterItem() :
    _id( "" ),
    _amount( 0 ),
    _item( nullptr ) {}

std::string CharacterItem::id() const {
    return _id;
}

void CharacterItem::setId( const std::string& id ) {
    _id = id;
}

int CharacterItem::amount() const {
    return _amount;
}

void CharacterItem::setAmount( int amount ) {
    _amount = amount;
}

Item* CharacterItem::item() const {
    return _item;
}

void CharacterItem::setItem( Item* item ) {
    _item = item;
}

} // namespace Model
