#ifndef MESSAGEHELPER_H
#define MESSAGEHELPER_H

#include <string>

#include "MessageType.h"

using System::Message::MessageType;

namespace System::Message {

class MessageHelper {
public:
    static MessageType stringToType( const std::string& type );
    static std::string typeToString( const MessageType type );
};

} // namespace System::Message

#endif // MESSAGEHELPER_H
