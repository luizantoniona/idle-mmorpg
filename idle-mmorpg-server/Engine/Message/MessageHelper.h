#ifndef MESSAGEHELPER_H
#define MESSAGEHELPER_H

#include <string>

#include "MessageReceiverType.h"
#include "MessageSenderType.h"

namespace Core::Message {

class MessageHelper {
public:
    static MessageReceiverType stringToType( const std::string& type );
    static std::string typeToString( const MessageSenderType type );
};

} // namespace Core::Message

#endif // MESSAGEHELPER_H
