#ifndef PROGRESSIONSYSTEM_H
#define PROGRESSIONSYSTEM_H

#include <string>

#include <Core/Message/MessageSender.h>
#include <Model/Character/Character.h>

namespace Core::System {

class ProgressionSystem {
public:
    ProgressionSystem();

    void notifyCharacterProgression( const std::string& sessionId, Model::Character* character );
    void notifyCharacterSkills( const std::string& sessionId, Model::Character* character );

    void applyExperience( const std::string& sessionId, Model::Character* character, const std::string& skillId, int xpGained );

private:
    Core::Message::MessageSender _sender;
};

} // namespace Core::System

#endif // PROGRESSIONSYSTEM_H
