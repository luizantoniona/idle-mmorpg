#ifndef SKILLPROGRESSIONSYSTEM_H
#define SKILLPROGRESSIONSYSTEM_H

#include <string>

#include <Core/Message/MessageSender.h>
#include <Model/Character/Character.h>

namespace Core::System {

class SkillProgressionSystem {
public:
    SkillProgressionSystem();

    void notifyCharacterSkills( const std::string& sessionId, Model::Character* character );

    void applyExperience( const std::string& sessionId, Model::Character* character, const std::string& skillId, int xpGained );

private:
    Core::Message::MessageSender _sender;
};

} // namespace Core::System

#endif // SKILLPROGRESSIONSYSTEM_H
