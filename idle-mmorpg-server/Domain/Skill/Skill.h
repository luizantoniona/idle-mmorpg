#ifndef SKILL_H
#define SKILL_H

#include <string>
#include <vector>

#include <json/json.h>

#include "SkillMilestone.h"
#include "SkillType.h"

namespace Domain {

class Skill {
public:
    Skill();

    Json::Value toJson();

    SkillType type() const;
    void setType( SkillType type );

    std::string category() const;
    void setCategory( const std::string& category );

    std::string name() const;
    void setName( const std::string& name );

    std::string description() const;
    void setDescription( const std::string& description );

    SkillMilestone milestone() const;
    void setMilestone( const SkillMilestone& milestone );

    double baseExperience() const;
    void setBaseExperience( double baseExperience );

    double growthRate() const;
    void setGrowthRate( double growthRate );

    int experienceForNextLevel( int currentLevel ) const;

private:
    SkillType _type;
    std::string _category;
    std::string _name;
    std::string _description;
    SkillMilestone _milestone;

    double _baseExperience;
    double _growthRate;
};

} // namespace Domain

#endif // SKILL_H
