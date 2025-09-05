#include "ItemBonus.h"

namespace Model {

ItemBonus::ItemBonus() :
    _id( "" ),
    _value( 0.0 ) {}

Json::Value ItemBonus::toJson() {
    Json::Value root;
    root[ "id" ] = id();
    root[ "value" ] = value();

    return root;
}

std::string ItemBonus::type() const {
    return _type;
}

void ItemBonus::setType( const std::string& type ) {
    _type = type;
}

std::string ItemBonus::id() const {
    return _id;
}

void ItemBonus::setId( const std::string& id ) {
    _id = id;
}

double ItemBonus::value() const {
    return _value;
}

void ItemBonus::setValue( double value ) {
    _value = value;
}

} // namespace Model
