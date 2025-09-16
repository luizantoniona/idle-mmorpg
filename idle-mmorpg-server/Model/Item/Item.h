#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>

#include <json/json.h>

#include "ItemBonus.h"
#include "ItemEffect.h"

namespace Model {

class Item {
public:
    Item();

    Json::Value toJson() const;

    std::string id() const;
    void setId( const std::string& id );

    std::string type() const;
    void setType( const std::string& type );

    std::string category() const;
    void setCategory( const std::string& category );

    std::string name() const;
    void setName( const std::string& name );

    std::string description() const;
    void setDescription( const std::string& description );

    std::string rarity() const;
    void setRarity( const std::string& rarity );

    std::string icon() const;
    void setIcon( const std::string& icon );

    int price() const;
    void setPrice( int price );

    std::vector<ItemBonus> bonuses() const;
    void setBonuses( const std::vector<ItemBonus>& bonuses );
    void addBonus( const ItemBonus& bonus );

    std::vector<ItemEffect> effects() const;
    void setEffects( const std::vector<ItemEffect>& effects );
    void addEffect( const ItemEffect& effect );

private:
    std::string _id;
    std::string _type;
    std::string _category;
    std::string _name;
    std::string _description;
    std::string _rarity;
    std::string _icon;
    int _price;
    std::vector<ItemBonus> _bonuses;
    std::vector<ItemEffect> _effects;
};

} // namespace Model

#endif // ITEM_H
