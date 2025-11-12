#include "ItemEffect.h"

namespace Domain {

ItemEffect::ItemEffect() :
    _type( "" ),
    _category( "" ),
    _value( 0.0 ),
    _duration( 0 ) {
}

Json::Value ItemEffect::toJson() const {
    Json::Value root;
    root[ "type" ] = type();
    root[ "category" ] = category();
    root[ "value" ] = value();
    root[ "duration" ] = duration();
    return root;
}

std::string ItemEffect::type() const {
    return _type;
}

void ItemEffect::setType( const std::string& type ) {
    _type = type;
}

std::string ItemEffect::category() const {
    return _category;
}

void ItemEffect::setCategory( const std::string& category ) {
    _category = category;
}

double ItemEffect::value() const {
    return _value;
}

void ItemEffect::setValue( double value ) {
    _value = value;
}

int ItemEffect::duration() const {
    return _duration;
}

void ItemEffect::setDuration( int duration ) {
    _duration = duration;
}

} // namespace Domain
