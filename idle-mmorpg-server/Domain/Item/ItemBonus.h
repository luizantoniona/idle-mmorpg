#ifndef ITEMBONUS_H
#define ITEMBONUS_H

#include <string>

#include <json/json.h>

#include <Domain/Skill/SkillType.h>

namespace Domain {

class ItemBonus {
public:
    ItemBonus();

    Json::Value toJson() const;

    SkillType type() const;
    void setType( SkillType type );

    double value() const;
    void setValue( double value );

private:
    SkillType _type;
    double _value;
};

} // namespace Domain

#endif // ITEMBONUS_H
