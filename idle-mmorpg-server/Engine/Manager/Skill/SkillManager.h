#ifndef SKILLMANAGER_H
#define SKILLMANAGER_H

#include <memory>
#include <string>
#include <unordered_map>

#include <Domain/Skill/Skill.h>

namespace Engine {

class SkillManager {
public:
    SkillManager();

    void initialize( const std::string& skillsPath );

    Domain::Skill* skill( const std::string& idSkill );
    Domain::Skill* skill( Domain::SkillType typeSkill );

private:
    std::unordered_map<std::string, std::unique_ptr<Domain::Skill> > _skills;
};

} // namespace Engine

#endif // SKILLMANAGER_H
