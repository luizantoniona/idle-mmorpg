#include "ItemModifier.h"

namespace {
constexpr const char* JSON_TYPE = "type";
constexpr const char* JSON_TARGET = "target";
constexpr const char* JSON_VALUE = "value";
} // namespace

namespace Model {

ItemModifier::ItemModifier() :
    _type( "" ),
    _target( "" ),
    _value( 0.0 ) {}

Json::Value ItemModifier::toJson() {
    Json::Value root;
    root[ JSON_TYPE ] = type();
    root[ JSON_TARGET ] = target();
    root[ JSON_VALUE ] = value();

    return root;
}

std::string ItemModifier::type() const {
    return _type;
}

void ItemModifier::setType( const std::string& type ) {
    _type = type;
}

std::string ItemModifier::target() const {
    return _target;
}

void ItemModifier::setTarget( const std::string& target ) {
    _target = target;
}

double ItemModifier::value() const {
    return _value;
}

void ItemModifier::setValue( double value ) {
    _value = value;
}

} // namespace Model
