#ifndef PROGRESSIONSYSTEM_H
#define PROGRESSIONSYSTEM_H

#include <string>

#include <Core/System/NotificationSystem.h>
#include <Core/Message/MessageSender.h>
#include <Model/Character/Character.h>
#include <Model/Skill/Skill.h>

#include "NotificationSystem.h"

namespace Core::System {

class ProgressionSystem {
public:
    ProgressionSystem();

    void applyExperience( const std::string& sessionId, Model::Character* character, const std::string& skillId, int xpGained );
    void applyMilestone( Model::Character* character, Model::CharacterSkill* characterSkill );
    void applyMilestoneBonus( Model::Character* character, const Model::SkillMilestoneBonus milestoneBonus );

private:
    NotificationSystem _notificationSystem;
};

} // namespace Core::System

#endif // PROGRESSIONSYSTEM_H
