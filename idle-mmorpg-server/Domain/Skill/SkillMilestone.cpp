#include "SkillMilestone.h"

namespace Domain {

SkillMilestone::SkillMilestone() :
    _type( SkillMilestoneType::UNKNOWN ),
    _value( 0.0 ),
    _interval( 0 ) {}

SkillMilestoneType SkillMilestone::type() const {
    return _type;
}

double SkillMilestone::value() const {
    return _value;
}

void SkillMilestone::setValue( double value ) {
    _value = value;
}

void SkillMilestone::setType( SkillMilestoneType type ) {
    _type = type;
}

int SkillMilestone::interval() const {
    return _interval;
}

void SkillMilestone::setInterval( int interval ) {
    _interval = interval;
}

} // namespace Domain
