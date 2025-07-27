#ifndef SKILLFACTORY_H
#define SKILLFACTORY_H

#include <string>
#include <memory>
#include <unordered_map>

#include <Model/Skill/Skill.h>

namespace Core::Factory {

class SkillFactory {
public:
    static std::unordered_map<std::string, std::unique_ptr<Model::Skill> > createSkills( const std::string& skillsPath );

private:
    static std::unique_ptr<Model::Skill> createSkill( const std::string& skillPath );
};

} // namespace Core::Factory

#endif // SKILLFACTORY_H
