#ifndef CHARACTERMESSAGESENDER_H
#define CHARACTERMESSAGESENDER_H

#include <drogon/WebSocketConnection.h>
#include <json/json.h>

#include <Engine/Message/MessageSenderType.h>

namespace Engine {

class CharacterMessageSender {
public:
    CharacterMessageSender( drogon::WebSocketConnectionPtr connection );

    void sendMessage( MessageSenderType type, const Json::Value& payload ) const;

private:
    drogon::WebSocketConnectionPtr _connection;
};

} // namespace Engine

#endif // CHARACTERMESSAGESENDER_H
