#include "Item.h"

#include "ItemHelper.h"

namespace Domain {

Item::Item() :
    _id( "" ),
    _type( ItemType::UNKNOWN ),
    _category( ItemCategoryType::UNKNOWN ),
    _name( "" ),
    _description( "" ),
    _icon( "" ),
    _price( 0 ),
    _bonus(),
    _combat(),
    _effect() {}

Json::Value Item::toJson() const {
    Json::Value root;
    root[ "id" ] = _id;
    root[ "type" ] = ItemHelper::typeToString( _type );
    root[ "category" ] = ItemHelper::categoryTypeToString( _category );
    root[ "name" ] = _name;
    root[ "description" ] = _description;
    root[ "icon" ] = _icon;
    root[ "price" ] = _price;

    root[ "bonus" ].append( _bonus.toJson() );
    root[ "combat" ] = _combat.toJson();
    root[ "effect" ].append( _effect.toJson() );

    return root;
}

std::string Item::id() const {
    return _id;
}

void Item::setId( const std::string& id ) {
    _id = id;
}

ItemType Item::type() const {
    return _type;
}

void Item::setType( ItemType type ) {
    _type = type;
}

ItemCategoryType Item::category() const {
    return _category;
}

void Item::setCategory( ItemCategoryType category ) {
    _category = category;
}

std::string Item::name() const {
    return _name;
}

void Item::setName( const std::string& name ) {
    _name = name;
}

std::string Item::description() const {
    return _description;
}

void Item::setDescription( const std::string& description ) {
    _description = description;
}

std::string Item::icon() const {
    return _icon;
}

void Item::setIcon( const std::string& icon ) {
    _icon = icon;
}

int Item::price() const {
    return _price;
}

void Item::setPrice( int price ) {
    _price = price;
}

ItemBonus Item::bonus() const {
    return _bonus;
}

void Item::setBonus( const ItemBonus& bonus ) {
    _bonus = bonus;
}

ItemCombat Item::combat() const {
    return _combat;
}

void Item::setCombat( const ItemCombat& combat ) {
    _combat = combat;
}

ItemEffect Item::effect() const {
    return _effect;
}

void Item::setEffect( const ItemEffect& effect ) {
    _effect = effect;
}

} // namespace Domain
