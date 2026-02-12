#ifndef CHARACTERSKILLSCONTROLLER_H
#define CHARACTERSKILLSCONTROLLER_H

#include <Domain/Character/CharacterSkills.h>
#include <Manager/Skill/SkillManager.h>

namespace Engine {

class CharacterSkillsController {
public:
    explicit CharacterSkillsController( Domain::CharacterSkills& skills, Manager::SkillManager& skillManager );

    void onEnterWorld();
    void onExitWorld();

    void tick();

private:
    Domain::CharacterSkills& _skills;
    Manager::SkillManager& _skillManager;
};

} // namespace Engine

#endif // CHARACTERSKILLSCONTROLLER_H
