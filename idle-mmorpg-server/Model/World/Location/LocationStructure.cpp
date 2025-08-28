#include "LocationStructure.h"

namespace Model {

LocationStructure::LocationStructure() :
    _id( "" ),
    _label( "" ),
    _description( "" ),
    _x( 0 ),
    _y( 0 ) {}

Json::Value LocationStructure::toJson() const {
    Json::Value root;
    root[ "id" ] = id();
    root[ "label" ] = label();
    root[ "description" ] = description();
    root[ "x" ] = x();
    root[ "y" ] = y();
    return root;
}

std::string LocationStructure::id() const {
    return _id;
}

void LocationStructure::setId( const std::string& id ) {
    _id = id;
}

std::string LocationStructure::label() const {
    return _label;
}

void LocationStructure::setLabel( const std::string& label ) {
    _label = label;
}

std::string LocationStructure::description() const {
    return _description;
}

void LocationStructure::setDescription( const std::string& description ) {
    _description = description;
}

int LocationStructure::x() const {
    return _x;
}

void LocationStructure::setX( int x ) {
    _x = x;
}

int LocationStructure::y() const {
    return _y;
}

void LocationStructure::setY( int y ) {
    _y = y;
}

} // namespace Model
