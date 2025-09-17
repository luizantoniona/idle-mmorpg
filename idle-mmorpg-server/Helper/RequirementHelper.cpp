#include "RequirementHelper.h"

#include <iostream>

namespace Helper {

Model::RequirementType RequirementHelper::stringToEnum( const std::string& type ) {
    if ( type == "skill" ) {
        return Model::RequirementType::SKILL;

    } else if ( type == "item" ) {
        return Model::RequirementType::ITEM;

    } else if ( type == "equipment" ) {
        return Model::RequirementType::EQUIPMENT;

    } else if ( type == "quest" ) {
        return Model::RequirementType::QUEST;
    }

    std::cerr << "RequirementHelper::stringToEnum Unknow type: " << type << std::endl;
    return Model::RequirementType::UNKNOWN;
}

} // namespace Helper
