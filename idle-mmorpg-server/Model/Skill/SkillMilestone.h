#ifndef SKILLMILESTONE_H
#define SKILLMILESTONE_H

#include <vector>

#include "SkillMilestoneBonus.h"

namespace Model {

class SkillMilestone {
public:
    SkillMilestone();

    int level() const;
    void setLevel( int level );

    std::vector<SkillMilestoneBonus> bonuses() const;
    void setBonuses( const std::vector<SkillMilestoneBonus>& bonuses );
    void addBonus( const SkillMilestoneBonus& bonus );

private:
    int _level;
    std::vector<SkillMilestoneBonus> _bonuses;
};

} // namespace Model

#endif // SKILLMILESTONE_H
