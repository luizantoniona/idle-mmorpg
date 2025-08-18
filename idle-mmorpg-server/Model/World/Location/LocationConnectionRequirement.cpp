#include "LocationConnectionRequirement.h"

namespace Model {

LocationConnectionRequirement::LocationConnectionRequirement() :
    _type( "" ),
    _id( "" ),
    _amount( 0 ) {}

std::string LocationConnectionRequirement::type() const {
    return _type;
}

void LocationConnectionRequirement::setType( const std::string& type ) {
    _type = type;
}

std::string LocationConnectionRequirement::id() const {
    return _id;
}

void LocationConnectionRequirement::setId( const std::string& id ) {
    _id = id;
}

int LocationConnectionRequirement::amount() const {
    return _amount;
}

void LocationConnectionRequirement::setAmount( int amount ) {
    _amount = amount;
}

} // namespace Model
