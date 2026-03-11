#include "Item.h"

#include "ItemHelper.h"

namespace Domain {

Item::Item() :
    _id( "" ),
    _type( ItemType::UNKNOWN ),
    _category( ItemCategory::UNKNOWN ),
    _name( "" ),
    _description( "" ),
    _icon( "" ),
    _price( 0 ),
    _combat(),
    _bonuses( {} ),
    _effects( {} ) {
}

Json::Value Item::toJson() const {
    Json::Value root;
    root[ "id" ] = _id;
    root[ "type" ] = ItemHelper::typeToString( _type );
    root[ "category" ] = ItemHelper::categoryToString( _category );
    root[ "name" ] = _name;
    root[ "description" ] = _description;
    root[ "icon" ] = _icon;
    root[ "price" ] = _price;

    root[ "combat" ] = _combat.toJson();

    for ( const ItemBonus& bonus : _bonuses ) {
        root[ "bonuses" ].append( bonus.toJson() );
    }

    for ( const ItemEffect& effect : _effects ) {
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

ItemType Item::type() const {
    return _type;
}

void Item::setType( ItemType type ) {
    _type = type;
}

ItemCategory Item::category() const {
    return _category;
}

void Item::setCategory( ItemCategory category ) {
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

ItemCombat Item::combat() const {
    return _combat;
}

void Item::setCombat( const ItemCombat& combat ) {
    _combat = combat;
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

} // namespace Domain
