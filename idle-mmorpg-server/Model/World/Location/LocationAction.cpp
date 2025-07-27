#include "LocationAction.h"

namespace Model {

LocationAction::LocationAction() :
    _id( "" ),
    _label( "" ),
    _requirements( {} ) {
}

Json::Value LocationAction::toJson() {
    Json::Value root;

    root[ "id" ] = id();
    root[ "label" ] = label();

    return root;
}

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

int LocationAction::duration() const {
    return _duration;
}

void LocationAction::setDuration( int duration ) {
    _duration = duration;
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

std::vector<LocationActionExperience> LocationAction::experience() const {
    return _experience;
}

void LocationAction::setExperience( const std::vector<LocationActionExperience>& experience ) {
    _experience = experience;
}

void LocationAction::addExperience( const LocationActionExperience& experience ) {
    _experience.push_back( experience );
}

} // namespace Model
