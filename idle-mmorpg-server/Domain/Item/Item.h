#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>

#include <json/json.h>

#include "ItemBonus.h"
#include "ItemCombat.h"
#include "ItemEffect.h"

#include "ItemCategory.h"
#include "ItemType.h"

namespace Domain {

class Item {
public:
    Item();

    Json::Value toJson() const;

    std::string id() const;
    void setId( const std::string& id );

    ItemType type() const;
    void setType( ItemType type );

    ItemCategory category() const;
    void setCategory( ItemCategory category );

    std::string name() const;
    void setName( const std::string& name );

    std::string description() const;
    void setDescription( const std::string& description );

    std::string icon() const;
    void setIcon( const std::string& icon );

    int price() const;
    void setPrice( int price );

    ItemCombat combat() const;
    void setCombat( const ItemCombat& combat );

    std::vector<ItemBonus> bonuses() const;
    void setBonuses( const std::vector<ItemBonus>& bonuses );
    void addBonus( const ItemBonus& bonus );

    std::vector<ItemEffect> effects() const;
    void setEffects( const std::vector<ItemEffect>& effects );
    void addEffect( const ItemEffect& effect );

private:
    std::string _id;
    ItemType _type;
    ItemCategory _category;
    std::string _name;
    std::string _description;
    std::string _icon;
    int _price;

    ItemCombat _combat;
    std::vector<ItemBonus> _bonuses;
    std::vector<ItemEffect> _effects;
};

} // namespace Domain

#endif // ITEM_H
