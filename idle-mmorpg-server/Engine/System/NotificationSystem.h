#ifndef NOTIFICATIONSYSTEM_H
#define NOTIFICATIONSYSTEM_H

#include <string>

#include <Domain/Character/Character.h>
#include <Domain/World/Location/Location.h>
#include <Engine/Instance/CombatInstance.h>

namespace Engine {

class NotificationSystem {
public:
    static void notifyFullCharacter( const std::string& sessionId, Domain::Character* character );
    static void notifyDeadCharacter( const std::string& sessionId );
    static void notifyCharacterAttributes( const std::string& sessionId, Domain::Character* character );
    static void notifyCharacterEffects( const std::string& sessionId, Domain::Character* character );
    static void notifyCharacterEquipment( const std::string& sessionId, Domain::Character* character );
    static void notifyCharacterInventory( const std::string& sessionId, Domain::Character* character );
    static void notifyCharacterProgression( const std::string& sessionId, Domain::Character* character );
    static void notifyCharacterQuests( const std::string& sessionId, Domain::Character* character );
    static void notifyCharacterSkills( const std::string& sessionId, Domain::Character* character );
    static void notifyCharacterSpells( const std::string& sessionId, Domain::Character* character );
    static void notifyCharacterVitals( const std::string& sessionId, Domain::Character* character );
    static void notifyCharacterWallet( const std::string& sessionId, Domain::Character* character );

    static void notifyCurrentAction( const std::string& sessionId, Domain::Character* character );
    static void notifyCurrentCoordinates( const std::string& sessionId, Domain::Character* character );

    static void notifyFullLocation( const std::string& sessionId, const Domain::Location* location );
    static void notifyLocationActions( const std::string& sessionId, Domain::Character* character, const Domain::Location* location );
    static void notifyLocationConnections( const std::string& sessionId, Domain::Character* character, const Domain::Location* location );
    static void notifyLocationDenizens( const std::string& sessionId, Domain::Character* character, const Domain::Location* location );

    static void notifyCombatInstances( const std::string& sessionId, std::vector<Engine::CombatInstance*> combatInstances );
    static void notifyCombat( const Engine::CombatInstance* combatInstance );
};

} // namespace Engine

#endif // NOTIFICATIONSYSTEM_H
