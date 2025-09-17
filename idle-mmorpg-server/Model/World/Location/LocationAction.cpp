#include "LocationAction.h"

namespace Model {

LocationAction::LocationAction() :
    _id( "" ),
    _type( "" ),
    _label( "" ),
    _structure( "" ),
    _duration( 0 ),
    _requirements( {} ),
    _experience( {} ) {}

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

std::string LocationAction::type() const {
    return _type;
}

void LocationAction::setType( const std::string& type ) {
    _type = type;
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

std::vector<Requirement> LocationAction::requirements() const {
    return _requirements;
}

void LocationAction::setRequirements( const std::vector<Requirement>& requirements ) {
    _requirements = requirements;
}

void LocationAction::addRequirement( const Requirement& requirement ) {
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

std::vector<LocationActionLoot> LocationAction::loot() const {
    return _loot;
}

void LocationAction::setLoot( const std::vector<LocationActionLoot>& loot ) {
    _loot = loot;
}

void LocationAction::addLoot( const LocationActionLoot& loot ) {
    _loot.push_back( loot );
}

} // namespace Model
