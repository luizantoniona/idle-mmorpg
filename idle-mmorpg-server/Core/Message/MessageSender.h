#ifndef MESSAGESENDER_H
#define MESSAGESENDER_H

#include <string>

#include <json/json.h>

#include "MessageType.h"

namespace System::Message {

class MessageSender {
public:
    MessageSender();

    void send( const std::string& sessionId, const std::string& message );
    void send( const std::string& sessionId, MessageType type, const Json::Value& payload );
};

} // namespace System

#endif // MESSAGESENDER_H
