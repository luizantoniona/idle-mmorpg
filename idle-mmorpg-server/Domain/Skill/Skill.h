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

    std::string id() const;
    void setId( const std::string& id );

    std::string name() const;
    void setName( const std::string& name );

    std::string description() const;
    void setDescription( const std::string& description );

    std::string category() const;
    void setCategory( const std::string& category );

    std::vector<SkillMilestone> millestones() const;
    void setMillestones( const std::vector<SkillMilestone>& millestones );
    void addMilestone( const SkillMilestone& milestone );

    SkillType type() const;
    void setType( SkillType type );

private:
    SkillType _type;
    std::string _id;
    std::string _name;
    std::string _description;
    std::string _category;
    std::vector<SkillMilestone> _millestones;
};

} // namespace Domain

#endif // SKILL_H
