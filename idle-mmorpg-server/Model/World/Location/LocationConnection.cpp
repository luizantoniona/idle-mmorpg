#include "LocationConnection.h"

namespace Model {

LocationConnection::LocationConnection() :
    _destination( "" ),
    _structure( "" ),
    _label( "" ),
    _requirements( {} ) {}

Json::Value LocationConnection::toJson() {
    Json::Value root;
    root[ "destination" ] = destination();
    root[ "label" ] = label();
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

std::vector<LocationConnectionRequirement> LocationConnection::requirements() const {
    return _requirements;
}

void LocationConnection::setRequirements( const std::vector<LocationConnectionRequirement>& requirements ) {
    _requirements = requirements;
}

void LocationConnection::addRequirement( const LocationConnectionRequirement& requirement ) {
    _requirements.push_back( requirement );
}

} // namespace Model
