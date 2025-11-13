#ifndef PROGRESSIONSYSTEM_H
#define PROGRESSIONSYSTEM_H

#include <string>

#include <Domain/Character/Character.h>
#include <Domain/Skill/Skill.h>

namespace Engine {

class ProgressionSystem {
public:
    ProgressionSystem();

    void applyExperience( const std::string& sessionId, Domain::Character* character, const Domain::SkillType& skillType, int xpGained );
    void applyMilestone( Domain::Character* character, Domain::CharacterSkill* characterSkill );
    void applyMilestoneBonus( Domain::Character* character, const Domain::SkillMilestoneBonus milestoneBonus );

    void applyExperience( const std::string& sessionId, Domain::Character* character, int xpGained );
    void applyLevelUp( Domain::Character* character );
};

} // namespace Engine

#endif // PROGRESSIONSYSTEM_H
