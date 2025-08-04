#ifndef SKILL_H
#define SKILL_H

#include <string>
#include <vector>

#include <json/json.h>

#include "SkillMilestone.h"

namespace Model {

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

    std::string type() const;
    void setType( const std::string& type );

    std::vector<SkillMilestone> millestones() const;
    void setMillestones( const std::vector<SkillMilestone>& millestones );
    void addMilestone( const SkillMilestone& milestone );

private:
    std::string _id;
    std::string _name;
    std::string _description;
    std::string _type;
    std::vector<SkillMilestone> _millestones;
};

} // namespace Model

#endif // SKILL_H
