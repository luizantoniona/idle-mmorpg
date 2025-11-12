#include "RequirementHelper.h"

#include <iostream>

namespace Helper {

Domain::RequirementType RequirementHelper::stringToEnum( const std::string& type ) {
    if ( type == "skill" ) {
        return Domain::RequirementType::SKILL;

    } else if ( type == "item" ) {
        return Domain::RequirementType::ITEM;

    } else if ( type == "equipment" ) {
        return Domain::RequirementType::EQUIPMENT;

    } else if ( type == "quest" ) {
        return Domain::RequirementType::QUEST;
    }

    std::cerr << "RequirementHelper::stringToEnum Unknow type: " << type << std::endl;
    return Domain::RequirementType::UNKNOWN;
}

} // namespace Helper
