#include "Item.h"

namespace Model {

Item::Item() :
    _id( "" ),
    _type( "" ),
    _category( "" ),
    _name( "" ),
    _description( "" ),
    _rarity( "" ),
    _icon( "" ),
    _price( 0 ),
    _bonuses( {} ),
    _effects( {} ) {
}

Json::Value Item::toJson() const {
    Json::Value root;
    root[ "id" ] = id();
    root[ "type" ] = type();
    root[ "category" ] = category();
    root[ "name" ] = name();
    root[ "description" ] = description();
    root[ "rarity" ] = rarity();
    root[ "icon" ] = icon();
    root[ "price" ] = price();

    for ( ItemBonus& bonus : bonuses() ) {
        root[ "bonuses" ].append( bonus.toJson() );
    }

    for ( ItemEffect& effect : effects() ) {
        root[ "effects" ].append( effect.toJson() );
    }

    return root;
}

std::string Item::id() const {
    return _id;
}

void Item::setId( const std::string& id ) {
    _id = id;
}

std::string Item::type() const {
    return _type;
}

void Item::setType( const std::string& type ) {
    _type = type;
}

std::string Item::category() const {
    return _category;
}

void Item::setCategory( const std::string& category ) {
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

std::string Item::rarity() const {
    return _rarity;
}

void Item::setRarity( const std::string& rarity ) {
    _rarity = rarity;
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

std::vector<ItemBonus> Item::bonuses() const {
    return _bonuses;
}

void Item::setBonuses( const std::vector<ItemBonus>& bonuses ) {
    _bonuses = bonuses;
}

void Item::addBonus( const ItemBonus& bonus ) {
    _bonuses.push_back( bonus );
}

std::vector<ItemEffect> Item::effects() const {
    return _effects;
}

void Item::setEffects( const std::vector<ItemEffect>& effects ) {
    _effects = effects;
}

void Item::addEffect( const ItemEffect& effect ) {
    _effects.push_back( effect );
}

} // namespace Model
