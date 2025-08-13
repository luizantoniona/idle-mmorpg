#ifndef NOTIFICATIONSYSTEM_H
#define NOTIFICATIONSYSTEM_H

#include <string>

#include <Core/Instance/CombatInstance.h>
#include <Model/Character/Character.h>
#include <Model/World/Location/Location.h>

namespace Core::System {

class NotificationSystem {
public:
    static void notifyFullCharacter( const std::string& sessionId, Model::Character* character );
    static void notifyDeadCharacter( const std::string& sessionId );
    static void notifyCharacterAttributes( const std::string& sessionId, Model::Character* character );
    static void notifyCharacterCombatAttributes( const std::string& sessionId, Model::Character* character );
    static void notifyCharacterInventory( const std::string& sessionId, Model::Character* character );
    static void notifyCharacterProgression( const std::string& sessionId, Model::Character* character );
    static void notifyCharacterSkills( const std::string& sessionId, Model::Character* character );
    static void notifyCharacterVitals( const std::string& sessionId, Model::Character* character );
    static void notifyCharacterWallet( const std::string& sessionId, Model::Character* character );

    static void notifyCurrentAction( const std::string& sessionId, Model::Character* character );
    static void notifyCurrentCoordinates( const std::string& sessionId, Model::Character* character );

    static void notifyFullLocation( const std::string& sessionId, const Model::Location* location );
    static void notifyLocationActions( const std::string& sessionId, Model::Character* character, const Model::Location* location );
    static void notifyLocationConnections( const std::string& sessionId, Model::Character* character, const Model::Location* location );

    static void notifyCombatInstances( const std::string& sessionId, std::vector<Core::Instance::CombatInstance*> combatInstances );
    static void notifyCombat( const Instance::CombatInstance* combatInstance );
};

} // namespace Core::System

#endif // NOTIFICATIONSYSTEM_H
