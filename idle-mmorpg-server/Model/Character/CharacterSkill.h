#ifndef CHARACTERSKILL_H
#define CHARACTERSKILL_H

#include <string>

#include <json/json.h>

#include <Model/Skill/Skill.h>

namespace Model {

class CharacterSkill {
public:
    CharacterSkill();

    Json::Value toJson();

    std::string id() const;
    void setId( const std::string& id );

    int level() const;
    void setLevel( int level );

    int experience() const;
    void setExperience( int experience );

    Skill* skill() const;
    void setSkill( Skill* skill );

private:
    std::string _id;
    int _level;
    int _experience;
    Skill* _skill;
};

} // namespace Model

#endif // CHARACTERSKILL_H
