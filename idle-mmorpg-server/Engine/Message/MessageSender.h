#ifndef MESSAGESENDER_H
#define MESSAGESENDER_H

#include <string>

#include <json/json.h>

#include "MessageSenderType.h"

namespace Core::Message {

class MessageSender {
public:
    static void send( const std::string& sessionId, MessageSenderType type, const Json::Value& payload );
    static void send( const std::string& sessionId, const std::string& message );
};

} // namespace Core::Message

#endif // MESSAGESENDER_H
