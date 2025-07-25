#include "LocationActionRequirement.h"

namespace Model {

LocationActionRequirement::LocationActionRequirement() :
    _type( RequirementType::Unknown ),
    _id( "" ),
    _level( 0 ),
    _category( "" ) {}

std::string LocationActionRequirement::typeToString( RequirementType type ) {
    switch ( type ) {
        case RequirementType::Skill:
            return "skill";
        case RequirementType::Item:
            return "item";
        default:
            return "unknown";
    }
}

LocationActionRequirement::RequirementType LocationActionRequirement::typeFromString( const std::string& type ) {
    if ( type == "skill" )
        return RequirementType::Skill;
    if ( type == "item" )
        return RequirementType::Item;
    return RequirementType::Unknown;
}

LocationActionRequirement::RequirementType LocationActionRequirement::type() const {
    return _type;
}

void LocationActionRequirement::setType( RequirementType type ) {
    _type = type;
}

std::string LocationActionRequirement::id() const {
    return _id;
}

void LocationActionRequirement::setId( const std::string& id ) {
    _id = id;
}

int LocationActionRequirement::level() const {
    return _level;
}

void LocationActionRequirement::setLevel( int level ) {
    _level = level;
}

std::string LocationActionRequirement::category() const {
    return _category;
}

void LocationActionRequirement::setCategory( const std::string& category ) {
    _category = category;
}

} // namespace Model
