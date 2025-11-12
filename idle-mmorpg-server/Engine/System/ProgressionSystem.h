#ifndef PROGRESSIONSYSTEM_H
#define PROGRESSIONSYSTEM_H

#include <string>

#include <Core/Message/MessageSender.h>
#include <Domain/Character/Character.h>
#include <Domain/Skill/Skill.h>

namespace Core::System {

class ProgressionSystem {
public:
    ProgressionSystem();

    void applyExperience( const std::string& sessionId, Domain::Character* character, const Domain::SkillType& skillType, int xpGained );
    void applyMilestone( Domain::Character* character, Domain::CharacterSkill* characterSkill );
    void applyMilestoneBonus( Domain::Character* character, const Domain::SkillMilestoneBonus milestoneBonus );

    void applyExperience( const std::string& sessionId, Domain::Character* character, int xpGained );
    void applyLevelUp( Domain::Character* character );
};

} // namespace Core::System

#endif // PROGRESSIONSYSTEM_H
