#ifndef MESSAGERECEIVER_H
#define MESSAGERECEIVER_H

#include <string>

namespace Engine {

class MessageReceiver {
public:
    MessageReceiver();

    void receive( const std::string& sessionId, const std::string& message );
};

} // namespace Engine

#endif // MESSAGERECEIVER_H
