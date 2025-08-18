#include "LocationActionRequirement.h"

namespace Model {

LocationActionRequirement::LocationActionRequirement() :
    _type( "" ),
    _id( "" ),
    _amount( 0 ) {}

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

int LocationActionRequirement::amount() const {
    return _amount;
}

void LocationActionRequirement::setAmount( int amount ) {
    _amount = amount;
}

} // namespace Model
