#ifndef ITEM_H
#define ITEM_H

#include <string>

namespace Model {

class Item {
public:
    Item();

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

private:
    std::string _id;
    std::string _type;
    std::string _category;
    std::string _name;
    std::string _description;
    std::string _rarity;
    std::string _icon;
    int _value;

    // Create Item StatusModel
};

} // namespace Model

#endif // ITEM_H
