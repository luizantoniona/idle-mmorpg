#include "DenizenTrade.h"

namespace Model {

DenizenTrade::DenizenTrade() {}

Json::Value DenizenTrade::toJson() {
    Json::Value root;
    Json::Value sellArray;
    Json::Value buyArray;

    for ( auto& item : sellItems() ) {
        if ( item.item() ) {
            sellArray.append( item.item()->toJson() );
        }
    }

    for ( auto& item : buyItems() ) {
        if ( item.item() ) {
            buyArray.append( item.item()->toJson() );
        }
    }

    root[ "sell" ] = sellArray;
    root[ "buy" ] = buyArray;
    return root;
}

std::vector<DenizenTradeItem> DenizenTrade::sellItems() const {
    return _sellItems;
}

void DenizenTrade::setSellItems( const std::vector<DenizenTradeItem>& sellItems ) {
    _sellItems = sellItems;
}

void DenizenTrade::addSellItem( const DenizenTradeItem& sellItem ) {
    _sellItems.push_back( sellItem );
}

std::vector<DenizenTradeItem> DenizenTrade::buyItems() const {
    return _buyItems;
}

void DenizenTrade::setBuyItems( const std::vector<DenizenTradeItem>& buyItems ) {
    _buyItems = buyItems;
}

void DenizenTrade::addBuyItem( const DenizenTradeItem& buyItem ) {
    _buyItems.push_back( buyItem );
}

} // namespace Model
