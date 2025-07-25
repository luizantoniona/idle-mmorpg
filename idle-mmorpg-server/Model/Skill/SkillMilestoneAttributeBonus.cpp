#include "SkillMilestoneAttributeBonus.h"

namespace Model {

SkillMilestoneAttributeBonus::SkillMilestoneAttributeBonus() :
    _value( 0 ),
    _attribute( "" ) {}

int SkillMilestoneAttributeBonus::value() const {
    return _value;
}

void SkillMilestoneAttributeBonus::setValue( int value ) {
    _value = value;
}

std::string SkillMilestoneAttributeBonus::attribute() const {
    return _attribute;
}

void SkillMilestoneAttributeBonus::setAttribute( const std::string& attribute ) {
    _attribute = attribute;
}

}
