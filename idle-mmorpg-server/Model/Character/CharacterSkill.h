#ifndef CHARACTERSKILL_H
#define CHARACTERSKILL_H

#include <string>

#include <json/json.h>

#include <Model/Skill/Skill.h>
#include <Model/Skill/SkillType.h>

namespace Model {

class CharacterSkill {
public:
    CharacterSkill();

    Json::Value toJson();

    SkillType type() const;
    void setType( SkillType type );

    std::string id() const;
    void setId( const std::string& id );

    int level() const;
    void setLevel( int level );

    int bonusLevel() const;
    void setBonusLevel( int bonusLevel );
    void modifyBonusLevel( int modifier );

    int experience() const;
    void setExperience( int experience );

    void clear();

    Skill* skill() const;
    void setSkill( Skill* skill );

private:
    SkillType _type;
    std::string _id;
    int _level;
    int _bonusLevel;
    int _experience;
    Skill* _skill;
};

} // namespace Model

#endif // CHARACTERSKILL_H
