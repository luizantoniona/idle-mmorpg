#include "ItemModifier.h"

namespace Model {

ItemModifier::ItemModifier() :
    _type( "" ),
    _id( "" ),
    _value( 0.0 ) {
}

Json::Value ItemModifier::toJson() {
    Json::Value root;
    root[ "type" ] = type();
    root[ "id" ] = id();
    root[ "value" ] = value();

    return root;
}

std::string ItemModifier::type() const {
    return _type;
}

void ItemModifier::setType( const std::string& type ) {
    _type = type;
}

std::string ItemModifier::id() const {
    return _id;
}

void ItemModifier::setId( const std::string& id ) {
    _id = id;
}

double ItemModifier::value() const {
    return _value;
}

void ItemModifier::setValue( double value ) {
    _value = value;
}

} // namespace Model
