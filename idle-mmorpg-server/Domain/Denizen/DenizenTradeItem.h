#ifndef DENIZENTRADEITEM_H
#define DENIZENTRADEITEM_H

#include <string>

#include <Domain/Item/Item.h>

namespace Domain {

class DenizenTradeItem {
public:
    DenizenTradeItem();

    std::string id() const;
    void setId( const std::string& id );

    const Item* item() const;
    void setItem( const Item* item );

private:
    std::string _id;
    const Item* _item;
};

} // namespace Domain

#endif // DENIZENTRADEITEM_H
