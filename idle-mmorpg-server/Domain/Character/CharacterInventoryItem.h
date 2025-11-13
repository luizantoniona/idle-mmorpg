#ifndef CHARACTERINVENTORYITEM_H
#define CHARACTERINVENTORYITEM_H

#include <string>

#include <json/json.h>

#include <Domain/Item/Item.h>

namespace Domain {

class CharacterInventoryItem {
public:
    CharacterInventoryItem();

    Json::Value toJson();

    std::string id() const;
    void setId( const std::string& id );

    int amount() const;
    void setAmount( int amount );

    const Item* item() const;
    void setItem( const Item* item );

private:
    std::string _id;
    int _amount;
    const Item* _item;
};

} // namespace Domain

#endif // CHARACTERINVENTORYITEM_H
