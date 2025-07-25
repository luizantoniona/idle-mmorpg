#ifndef SKILLMILESTONEATTRIBUTEBONUS_H
#define SKILLMILESTONEATTRIBUTEBONUS_H

#include <string>

namespace Model {

class SkillMilestoneAttributeBonus {
public:
    SkillMilestoneAttributeBonus();

    int value() const;
    void setValue( int value );

    std::string attribute() const;
    void setAttribute( const std::string& attribute );

private:
    int _value;
    std::string _attribute;
};

}

#endif // SKILLMILESTONEATTRIBUTEBONUS_H
