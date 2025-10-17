#ifndef SKILLMANAGER_H
#define SKILLMANAGER_H

#include <memory>
#include <string>
#include <unordered_map>

#include <Model/Skill/Skill.h>

namespace Core::Manager {

class SkillManager {
public:
    SkillManager();

    void initialize( const std::string& skillsPath );

    Model::Skill* skill( const std::string& idSkill );
    Model::Skill* skill( Model::SkillType typeSkill );

private:
    std::unordered_map<std::string, std::unique_ptr<Model::Skill> > _skills;
};

} // namespace Core::Manager

#endif // SKILLMANAGER_H
