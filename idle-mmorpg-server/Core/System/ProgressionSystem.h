#ifndef PROGRESSIONSYSTEM_H
#define PROGRESSIONSYSTEM_H

#include <string>

#include <Core/Message/MessageSender.h>
#include <Model/Character/Character.h>
#include <Model/Skill/Skill.h>

namespace Core::System {

class ProgressionSystem {
public:
    ProgressionSystem();

    void applyExperience( const std::string& sessionId, Model::Character* character, const std::string& skillId, int xpGained );
    void applyMilestone( Model::Character* character, Model::CharacterSkill* characterSkill );
    void applyMilestoneBonus( Model::Character* character, const Model::SkillMilestoneBonus milestoneBonus );

    void applyExperience( const std::string& sessionId, Model::Character* character, int xpGained );
    void applyLevelUp( Model::Character* character );
};

} // namespace Core::System

#endif // PROGRESSIONSYSTEM_H
