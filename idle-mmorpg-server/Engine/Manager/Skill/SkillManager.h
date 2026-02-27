#ifndef SKILLMANAGER_H
#define SKILLMANAGER_H

#include <memory>
#include <string>
#include <unordered_map>

#include <Domain/Skill/Skill.h>

namespace Manager {

class SkillManager {
public:
    SkillManager();

    void initialize( const std::string& skillsPath );

    Domain::Skill* skill( const std::string& skillId );
    Domain::Skill* skill( Domain::SkillType skillType );

private:
    std::unordered_map<std::string, std::unique_ptr<Domain::Skill> > _skills;
};

} // namespace Manager

#endif // SKILLMANAGER_H
