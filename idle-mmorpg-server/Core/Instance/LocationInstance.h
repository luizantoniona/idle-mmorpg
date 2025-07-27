#ifndef LOCATIONINSTANCE_H
#define LOCATIONINSTANCE_H

#include <mutex>
#include <string>
#include <unordered_map>

#include <Core/Message/MessageSender.h>
#include <Core/System/ActionSystem.h>
#include <Model/Character/Character.h>
#include <Model/World/Location/Location.h>

namespace Core::Instance {

class LocationInstance {
public:
    explicit LocationInstance( Model::Location* location );

    bool addCharacter( const std::string& sessionId, Model::Character* character );
    void removeCharacter( const std::string& sessionId );

    void tick();

private:
    mutable std::mutex _mutex;
    Model::Location* _location;
    std::unordered_map<std::string, Model::Character*> _characters;
    Core::Message::MessageSender _sender;
    Core::System::ActionSystem _actionSystem;
};

} // namespace Core::Instance

#endif // LOCATIONINSTANCE_H
