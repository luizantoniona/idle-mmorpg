#ifndef CHARACTERSKILLSCONTROLLER_H
#define CHARACTERSKILLSCONTROLLER_H

#include <Domain/Character/CharacterSkills.h>
#include <Manager/Skill/SkillManager.h>

#include "CharacterController.h"

namespace Engine {

class CharacterSkillsController : public CharacterController {
public:
    explicit CharacterSkillsController( Domain::CharacterSkills& skills, Manager::SkillManager& skillManager );

    void onEnterWorld() override;
    void onTickWorld() override;
    void onExitWorld() override;

private:
    Domain::CharacterSkills& _skills;
    Manager::SkillManager& _skillManager;
};

} // namespace Engine

#endif // CHARACTERSKILLSCONTROLLER_H
