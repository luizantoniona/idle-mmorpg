#include "LocationActionRequirement.h"

namespace Model {

LocationActionRequirement::LocationActionRequirement() :
    _type( "" ),
    _id( "" ),
    _level( 0 ),
    _category( "" ) {
}

std::string LocationActionRequirement::type() const {
    return _type;
}

void LocationActionRequirement::setType( const std::string& type ) {
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
