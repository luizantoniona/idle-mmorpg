#ifndef CHARACTERSKILLSCONTROLLER_H
#define CHARACTERSKILLSCONTROLLER_H

#include <Domain/Character/Character.h>
#include <Domain/Skill/SkillType.h>
#include <Engine/Manager/Skill/SkillManager.h>
#include <Engine/Instance/Character/EventBus/CharacterEvent.h>
#include <Engine/Instance/Character/EventBus/CharacterEventType.h>

#include "CharacterController.h"

namespace Engine {

class CharacterSkillsController : public CharacterController {
public:
    explicit CharacterSkillsController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                        Domain::Character& character,
                                        Manager::SkillManager& skillManager );

    void onEnterWorld() override;
    void onLeaveWorld() override;

    void onTick() override;

private:
    void applyExperience( Domain::CharacterSkill* characterSkill, int xpGained );
    void applyMilestone( Domain::CharacterSkill* characterSkill );

    // --- EventBus methods ---
    void onSkillExperienceGained( const CharacterEvent& event );
    void onItemEquipped( const CharacterEvent& event );

private:
    Domain::CharacterSkills& _characterSkills;
    Manager::SkillManager& _skillManager;
};

} // namespace Engine

#endif // CHARACTERSKILLSCONTROLLER_H
