#ifndef SKILLMANAGER_H
#define SKILLMANAGER_H

#include <memory>
#include <string>
#include <unordered_map>

#include <Model/Skill/Skill.h>

namespace System::Manager {

class SkillManager {
public:
    SkillManager();

    void initialize( const std::string& skillsPath );

private:
    std::unordered_map<std::string, std::unique_ptr<Model::Skill> > _skills;
};

} // namespace System::Manager

#endif // SKILLMANAGER_H
