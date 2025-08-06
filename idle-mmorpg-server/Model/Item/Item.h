#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>

#include <json/json.h>

#include "ItemModifier.h"

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

    int value() const;
    void setValue( int value );

    std::vector<ItemModifier> modifiers() const;
    void setModifiers( const std::vector<ItemModifier>& modifiers );
    void addModifier( const ItemModifier& modifier );

private:
    std::string _id;
    std::string _type;
    std::string _category;
    std::string _name;
    std::string _description;
    std::string _rarity;
    std::string _icon;
    int _value;
    std::vector<ItemModifier> _modifiers;
};

} // namespace Model

#endif // ITEM_H
