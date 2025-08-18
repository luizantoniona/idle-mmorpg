#ifndef QUESTSYSTEM_H
#define QUESTSYSTEM_H

#include <Model/Character/Character.h>
#include <Model/World/Location/Location.h>

namespace Core::System {

class QuestSystem {
public:
    static void characterAcceptQuest( const std::string& sessionId, Model::Character* character, const Model::Location* location, const Json::Value& payload );
    static void characterFinishQuest( const std::string& sessionId, Model::Character* character, const Model::Location* location, const Json::Value& payload );

    static void updateKillQuest( const std::string& sessionId, Model::Character* character, const std::string& creatureId );
    static void updateItemQuest( const std::string& sessionId, Model::Character* character );
    static void updateTalkQuest( const std::string& sessionId, Model::Character* character, const std::string& denizenId );
};

} // namespace Core::System

#endif // QUESTSYSTEM_H
