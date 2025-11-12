#include "LocationConnection.h"

namespace Domain {

LocationConnection::LocationConnection() :
    _destination( "" ),
    _structure( "" ),
    _label( "" ),
    _x( 0 ),
    _y( 0 ),
    _requirements( {} ) {
}

Json::Value LocationConnection::toJson() {
    Json::Value root;
    root[ "destination" ] = destination();
    root[ "label" ] = label();
    root[ "x" ] = x();
    root[ "y" ] = y();
    return root;
}

std::string LocationConnection::destination() const {
    return _destination;
}

void LocationConnection::setDestination( const std::string& destination ) {
    _destination = destination;
}

std::string LocationConnection::structure() const {
    return _structure;
}

void LocationConnection::setStructure( const std::string& structure ) {
    _structure = structure;
}

std::string LocationConnection::label() const {
    return _label;
}

void LocationConnection::setLabel( const std::string& label ) {
    _label = label;
}

int LocationConnection::x() const {
    return _x;
}

void LocationConnection::setX( int x ) {
    _x = x;
}

int LocationConnection::y() const {
    return _y;
}

void LocationConnection::setY( int y ) {
    _y = y;
}

std::vector<Requirement> LocationConnection::requirements() const {
    return _requirements;
}

void LocationConnection::setRequirements( const std::vector<Requirement>& requirements ) {
    _requirements = requirements;
}

void LocationConnection::addRequirement( const Requirement& requirement ) {
    _requirements.push_back( requirement );
}

} // namespace Domain
