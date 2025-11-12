#ifndef SKILLFACTORY_H
#define SKILLFACTORY_H

#include <memory>
#include <string>
#include <unordered_map>

#include <Domain/Skill/Skill.h>

namespace Engine {

class SkillFactory {
public:
    static std::unordered_map<std::string, std::unique_ptr<Domain::Skill> > createSkills( const std::string& skillsPath );

private:
    static std::unique_ptr<Domain::Skill> createSkill( const std::string& skillPath );
};

} // namespace Engine

#endif // SKILLFACTORY_H
