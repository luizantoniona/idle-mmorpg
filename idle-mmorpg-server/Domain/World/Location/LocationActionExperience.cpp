#include "LocationActionExperience.h"

namespace Domain {

LocationActionExperience::LocationActionExperience() :
    _idSkill( "" ),
    _amount( 0 ) {
}

std::string LocationActionExperience::idSkill() const {
    return _idSkill;
}

void LocationActionExperience::setIdSkill( const std::string& idSkill ) {
    _idSkill = idSkill;
}

int LocationActionExperience::amount() const {
    return _amount;
}

void LocationActionExperience::setAmount( int amount ) {
    _amount = amount;
}

} // namespace Domain
