#ifndef MESSAGESENDER_H
#define MESSAGESENDER_H

#include <string>

#include <json/json.h>

#include "MessageSenderType.h"

namespace Engine {

class MessageSender {
public:
    static void send( const std::string& sessionId, MessageSenderType type, const Json::Value& payload );
    static void send( const std::string& sessionId, const std::string& message );
};

} // namespace Engine

#endif // MESSAGESENDER_H
