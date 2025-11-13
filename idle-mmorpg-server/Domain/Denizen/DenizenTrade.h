#ifndef DENIZENTRADE_H
#define DENIZENTRADE_H

#include <vector>

#include "DenizenTradeItem.h"

namespace Domain {

class DenizenTrade {
public:
    DenizenTrade();

    Json::Value toJson();

    std::vector<DenizenTradeItem> sellItems() const;
    void setSellItems( const std::vector<DenizenTradeItem>& sellItems );
    void addSellItem( const DenizenTradeItem& sellItem );

    std::vector<DenizenTradeItem> buyItems() const;
    void setBuyItems( const std::vector<DenizenTradeItem>& buyItems );
    void addBuyItem( const DenizenTradeItem& buyItem );

private:
    std::vector<DenizenTradeItem> _sellItems;
    std::vector<DenizenTradeItem> _buyItems;
};

} // namespace Domain

#endif // DENIZENTRADE_H
