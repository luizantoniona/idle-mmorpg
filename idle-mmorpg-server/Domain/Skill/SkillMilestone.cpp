#include "SkillMilestone.h"

namespace Domain {

SkillMilestone::SkillMilestone() :
    _level( 0 ),
    _bonuses( {} ) {
}

int SkillMilestone::level() const {
    return _level;
}

void SkillMilestone::setLevel( int level ) {
    _level = level;
}

std::vector<SkillMilestoneBonus> SkillMilestone::bonuses() const {
    return _bonuses;
}

void SkillMilestone::setBonuses( const std::vector<SkillMilestoneBonus>& bonuses ) {
    _bonuses = bonuses;
}

void SkillMilestone::addBonus( const SkillMilestoneBonus& bonus ) {
    _bonuses.push_back( bonus );
}

} // namespace Domain
