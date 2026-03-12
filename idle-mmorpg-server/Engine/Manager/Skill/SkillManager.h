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

    Domain::Skill* skill( Domain::SkillType skillType ) const;

private:
    std::unordered_map<Domain::SkillType, std::unique_ptr<Domain::Skill> > _skills;
};

} // namespace Manager

#endif // SKILLMANAGER_H
