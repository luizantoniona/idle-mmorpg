#ifndef MESSAGERECEIVER_H
#define MESSAGERECEIVER_H

#include <string>

namespace System::Message {

class MessageReceiver {
public:
    MessageReceiver();

    void receive( const std::string& sessionId, const std::string& message );
};

} // namespace System::Message

#endif // MESSAGERECEIVER_H
