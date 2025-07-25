#ifndef SKILLMILESTONE_H
#define SKILLMILESTONE_H

#include <vector>

#include "SkillMilestoneAttributeBonus.h"

namespace Model {

class SkillMilestone {
public:
    SkillMilestone();

    int level() const;
    void setLevel( int level );

    std::vector<SkillMilestoneAttributeBonus> bonuses() const;
    void setBonuses( const std::vector<SkillMilestoneAttributeBonus>& bonuses );
    void addBonus( const SkillMilestoneAttributeBonus& bonus );

private:
    int _level;
    std::vector<SkillMilestoneAttributeBonus> _bonuses;
};

}

#endif // SKILLMILESTONE_H
