#ifndef LOCATIONINSTANCE_H
#define LOCATIONINSTANCE_H

#include <mutex>
#include <string>
#include <unordered_map>

#include <Model/Character/Character.h>
#include <Model/World/Location/Location.h>
#include <System/Message/MessageSender.h>

namespace System::Instance {

class LocationInstance {
public:
    explicit LocationInstance( Model::Location* location );

    bool addCharacter( const std::string& sessionId, Model::Character* character );
    void removeCharacter( const std::string& sessionId );

    void tick();

private:
    mutable std::mutex _mutex;
    System::Message::MessageSender _sender;
    Model::Location* _location;
    std::unordered_map<std::string, Model::Character*> _characters;
};

} // namespace System::Instance

#endif // LOCATIONINSTANCE_H
