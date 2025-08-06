#include "LocationAction.h"

namespace {
constexpr const char* JSON_ID = "id";
constexpr const char* JSON_LABEL = "label";
} // namespace

namespace Model {

LocationAction::LocationAction() :
    _id( "" ),
    _label( "" ),
    _structure( "" ),
    _duration( 0 ),
    _requirements( {} ),
    _experience( {} ) {}

Json::Value LocationAction::toJson() {
    Json::Value root;
    root[ JSON_ID ] = id();
    root[ JSON_LABEL ] = label();
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

std::string LocationAction::structure() const {
    return _structure;
}

void LocationAction::setStructure( const std::string& structure ) {
    _structure = structure;
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
