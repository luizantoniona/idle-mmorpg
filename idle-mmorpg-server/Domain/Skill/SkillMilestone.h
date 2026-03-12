#ifndef SKILLMILESTONE_H
#define SKILLMILESTONE_H

#include <string>

#include "SkillMilestoneType.h"

namespace Domain {

class SkillMilestone {
public:
    SkillMilestone();

    SkillMilestoneType type() const;
    void setType( SkillMilestoneType type );

    double value() const;
    void setValue( double value );

    int interval() const;
    void setInterval( int interval );

private:
    SkillMilestoneType _type;
    double _value;
    int _interval;
};

} // namespace Domain

#endif // SKILLMILESTONE_H
