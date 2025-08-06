#include "Item.h"

namespace {
constexpr const char* JSON_ID = "id";
constexpr const char* JSON_TYPE = "type";
constexpr const char* JSON_CATEGORY = "category";
constexpr const char* JSON_NAME = "name";
constexpr const char* JSON_DESCRIPTION = "description";
constexpr const char* JSON_RARITY = "rarity";
constexpr const char* JSON_ICON = "icon";
constexpr const char* JSON_VALUE = "value";
constexpr const char* JSON_MODIFIERS = "modifiers";
} // namespace

namespace Model {

Item::Item() :
    _id( "" ),
    _type( "" ),
    _category( "" ),
    _name( "" ),
    _description( "" ),
    _rarity( "" ),
    _icon( "" ),
    _value( 0 ),
    _modifiers( {} ) {}

Json::Value Item::toJson() const {
    Json::Value root;
    root[ JSON_ID ] = id();
    root[ JSON_TYPE ] = type();
    root[ JSON_CATEGORY ] = category();
    root[ JSON_NAME ] = name();
    root[ JSON_DESCRIPTION ] = description();
    root[ JSON_RARITY ] = rarity();
    root[ JSON_ICON ] = icon();
    root[ JSON_VALUE ] = value();

    // for ( auto& modifier : modifiers() ) {
    //     root[ JSON_MODIFIERS ].append( modifier.toJson() );
    // }

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

int Item::value() const {
    return _value;
}

void Item::setValue( int value ) {
    _value = value;
}

std::vector<ItemModifier> Item::modifiers() const {
    return _modifiers;
}

void Item::setModifiers( const std::vector<ItemModifier>& modifiers ) {
    _modifiers = modifiers;
}

void Item::addModifier( const ItemModifier& modifier ) {
    _modifiers.push_back( modifier );
}

} // namespace Model
