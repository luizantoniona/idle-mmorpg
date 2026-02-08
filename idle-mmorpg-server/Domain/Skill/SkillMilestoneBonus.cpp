#include "SkillMilestoneBonus.h"

namespace Domain {

SkillMilestoneBonus::SkillMilestoneBonus() :
    _type( "" ),
    _id( "" ),
    _value( 0.0 ) {
}

std::string SkillMilestoneBonus::type() const {
    return _type;
}

void SkillMilestoneBonus::setType( const std::string& type ) {
    _type = type;
}

std::string SkillMilestoneBonus::id() const {
    return _id;
}

void SkillMilestoneBonus::setId( const std::string& id ) {
    _id = id;
}

double SkillMilestoneBonus::value() const {
    return _value;
}

void SkillMilestoneBonus::setValue( double value ) {
    _value = value;
}

} // namespace Domain
