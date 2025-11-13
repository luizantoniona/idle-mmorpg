#include "ItemBonus.h"

namespace Domain {

ItemBonus::ItemBonus() :
    _type( "" ),
    _category( "" ),
    _value( 0.0 ) {
}

Json::Value ItemBonus::toJson() {
    Json::Value root;
    root[ "type" ] = type();
    root[ "category" ] = category();
    root[ "value" ] = value();
    return root;
}

std::string ItemBonus::type() const {
    return _type;
}

void ItemBonus::setType( const std::string& type ) {
    _type = type;
}

std::string ItemBonus::category() const {
    return _category;
}

void ItemBonus::setCategory( const std::string& category ) {
    _category = category;
}

double ItemBonus::value() const {
    return _value;
}

void ItemBonus::setValue( double value ) {
    _value = value;
}

} // namespace Domain
