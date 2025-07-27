#ifndef MESSAGEHELPER_H
#define MESSAGEHELPER_H

#include <string>

#include "MessageType.h"

using Core::Message::MessageType;

namespace Core::Message {

class MessageHelper {
public:
    static MessageType stringToType( const std::string& type );
    static std::string typeToString( const MessageType type );
};

} // namespace Core::Message

#endif // MESSAGEHELPER_H
