#include "DenizenTradeItem.h"

namespace Domain {

DenizenTradeItem::DenizenTradeItem() :
    _id( "" ),
    _item( nullptr ) {}

std::string DenizenTradeItem::id() const {
    return _id;
}

void DenizenTradeItem::setId( const std::string& id ) {
    _id = id;
}

const Item* DenizenTradeItem::item() const {
    return _item;
}

void DenizenTradeItem::setItem( const Item* item ) {
    _item = item;
}

} // namespace Domain
