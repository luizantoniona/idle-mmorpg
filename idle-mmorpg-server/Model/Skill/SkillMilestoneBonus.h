#ifndef SKILLMILESTONEBONUS_H
#define SKILLMILESTONEBONUS_H

#include <string>

namespace Model {

class SkillMilestoneBonus {
public:
    SkillMilestoneBonus();

    std::string type() const;
    void setType( const std::string& type );

    std::string id() const;
    void setId( const std::string& id );

    int value() const;
    void setValue( int value );

private:
    std::string _type;
    std::string _id;
    int _value;
};

} // namespace Model

#endif // SKILLMILESTONEBONUS_H
