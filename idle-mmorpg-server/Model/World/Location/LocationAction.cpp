#include "LocationAction.h"

namespace Model {

LocationAction::LocationAction() {}

std::string LocationAction::id() const {
    return _id;
}

void LocationAction::setId( const std::string& id ) {
    _id = id;
}

std::string LocationAction::label() const {
    return _label;
}

void LocationAction::setLabel( const std::string& label ) {
    _label = label;
}

std::vector<LocationActionRequirement> LocationAction::requirements() const {
    return _requirements;
}

void LocationAction::setRequirements( const std::vector<LocationActionRequirement>& requirements ) {
    _requirements = requirements;
}

void LocationAction::addRequirement( const LocationActionRequirement& requirement ) {
    _requirements.push_back( requirement );
}

} // namespace Model
