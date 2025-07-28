#ifndef MESSAGESENDER_H
#define MESSAGESENDER_H

#include <string>

#include <json/json.h>

#include "MessageSenderType.h"

namespace Core::Message {

class MessageSender {
public:
    MessageSender();

    void send( const std::string& sessionId, const std::string& message );
    void send( const std::string& sessionId, MessageSenderType type, const Json::Value& payload );
};

} // namespace Core::Message

#endif // MESSAGESENDER_H
