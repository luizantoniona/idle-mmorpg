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
    Domain::CharacterSkills& _characterSkills;
    Manager::SkillManager& _skillManager;

    // --- EventBus methods ---
    void onSkillExperienceGained( const CharacterEvent& event );

    void applyExperience( Domain::CharacterSkill* characterSkill, int xpGained );
    void applyMilestone( Domain::CharacterSkill* characterSkill );
    void applyMilestoneBonus( const Domain::SkillMilestoneBonus& milestoneBonus );
};

} // namespace Engine

#endif // CHARACTERSKILLSCONTROLLER_H
