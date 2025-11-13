#ifndef MESSAGEHELPER_H
#define MESSAGEHELPER_H

#include <string>

#include "MessageReceiverType.h"
#include "MessageSenderType.h"

namespace Engine {

class MessageHelper {
public:
    static MessageReceiverType stringToType( const std::string& type );
    static std::string typeToString( const MessageSenderType type );
};

} // namespace Engine

#endif // MESSAGEHELPER_H
