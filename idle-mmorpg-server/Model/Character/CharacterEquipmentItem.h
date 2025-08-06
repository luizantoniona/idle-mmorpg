#ifndef CHARACTEREQUIPMENTITEM_H
#define CHARACTEREQUIPMENTITEM_H

#include <string>

#include <json/json.h>

#include <Model/Item/Item.h>

namespace Model {

class CharacterEquipmentItem {
public:
    CharacterEquipmentItem();

    Json::Value toJson();

    std::string id() const;
    void setId( const std::string& id );

    const Item* item() const;
    void setItem( const Item* item );

private:
    std::string _id;
    const Item* _item;
};

} // namespace Model

#endif // CHARACTEREQUIPMENTITEM_H
