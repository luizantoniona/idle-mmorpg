#include "SkillMilestone.h"

namespace Model {

SkillMilestone::SkillMilestone() :
    _level( 0 ),
    _bonuses( {} ) {}

int SkillMilestone::level() const {
    return _level;
}

void SkillMilestone::setLevel( int level ) {
    _level = level;
}

std::vector<SkillMilestoneAttributeBonus> SkillMilestone::bonuses() const {
    return _bonuses;
}

void SkillMilestone::setBonuses( const std::vector<SkillMilestoneAttributeBonus>& bonuses ) {
    _bonuses = bonuses;
}

void SkillMilestone::addBonus( const SkillMilestoneAttributeBonus& bonus ) {
    _bonuses.push_back( bonus );
}

}
