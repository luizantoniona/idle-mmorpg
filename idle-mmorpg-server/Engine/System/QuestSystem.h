#ifndef QUESTSYSTEM_H
#define QUESTSYSTEM_H

#include <Domain/Character/Character.h>
#include <Domain/World/Location/Location.h>

namespace Engine {

class QuestSystem {
public:
    static void characterAcceptQuest( const std::string& sessionId, Domain::Character* character, const Domain::Location* location, const Json::Value& payload );
    static void characterFinishQuest( const std::string& sessionId, Domain::Character* character, const Domain::Location* location, const Json::Value& payload );

    static void updateKillQuest( const std::string& sessionId, Domain::Character* character, const std::string& creatureId );
    static void updateItemQuest( const std::string& sessionId, Domain::Character* character );
    static void updateTalkQuest( const std::string& sessionId, Domain::Character* character, const std::string& denizenId );
};

} // namespace Engine

#endif // QUESTSYSTEM_H
