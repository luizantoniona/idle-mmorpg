#ifndef MESSAGERECEIVER_H
#define MESSAGERECEIVER_H

#include <string>

namespace Core::Message {

class MessageReceiver {
public:
    MessageReceiver();

    void receive( const std::string& sessionId, const std::string& message );
};

} // namespace Core::Message

#endif // MESSAGERECEIVER_H
