#ifndef NOTIFICATIONSYSTEM_H
#define NOTIFICATIONSYSTEM_H

#include <string>

#include <Core/Message/MessageSender.h>
#include <Model/Character/Character.h>
#include <Model/World/Location/Location.h>

namespace Core::System {

class NotificationSystem {
public:
    NotificationSystem();

    void notifyFullCharacter( const std::string& sessionId, Model::Character* character );
    void notifyCharacterAttributes( const std::string& sessionId, Model::Character* character );
    void notifyCharacterProgression( const std::string& sessionId, Model::Character* character );
    void notifyCharacterSkills( const std::string& sessionId, Model::Character* character );
    void notifyCharacterVitals( const std::string& sessionId, Model::Character* character );

    void notifyCurrentAction( const std::string& sessionId, Model::Character* character );
    void notifyCurrentCoordinates( const std::string& sessionId, Model::Character* character );

    void notifyFullLocation( const std::string& sessionId, const Model::Location* location );
    void notifyLocationActions( const std::string& sessionId, Model::Character* character, const Model::Location* location );

private:
    Message::MessageSender _sender;
};

} // namespace Core::System

#endif // NOTIFICATIONSYSTEM_H
