#ifndef CHARACTERSKILLSCONTROLLER_H
#define CHARACTERSKILLSCONTROLLER_H

#include <Domain/Character/CharacterSkills.h>
#include <Engine/Manager/Skill/SkillManager.h>

#include "CharacterController.h"

namespace Engine {

class CharacterSkillsController : public CharacterController {
public:
    explicit CharacterSkillsController( std::function<void( MessageSenderType, const Json::Value& )> sendMessage,
                                        Domain::CharacterSkills& skills,
                                        Manager::SkillManager& skillManager );

    void onEnterWorld() override;
    void onLeaveWorld() override;

    void onTick() override;

private:
    Domain::CharacterSkills& _skills;
    Manager::SkillManager& _skillManager;
};

} // namespace Engine

#endif // CHARACTERSKILLSCONTROLLER_H
