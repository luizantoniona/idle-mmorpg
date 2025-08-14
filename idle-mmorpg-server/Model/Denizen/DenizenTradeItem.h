#ifndef DENIZENTRADEITEM_H
#define DENIZENTRADEITEM_H

#include <string>

#include <Model/Item/Item.h>

namespace Model {

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

} // namespace Model

#endif // DENIZENTRADEITEM_H
