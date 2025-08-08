#ifndef LOCATIONINSTANCE_H
#define LOCATIONINSTANCE_H

#include <mutex>
#include <string>
#include <unordered_map>

#include <Core/Message/MessageReceiverType.h>
#include <Core/System/ActionSystem.h>
#include <Core/System/NotificationSystem.h>
#include <Core/System/TrainingSystem.h>
#include <Model/Character/Character.h>
#include <Model/World/Location/Location.h>

#include "CombatInstance.h"

namespace Core::Instance {

class LocationInstance {
public:
    explicit LocationInstance( Model::Location* location );

    bool addCharacter( const std::string& sessionId, Model::Character* character );
    void removeCharacter( const std::string& sessionId );

    void createCombat( const std::string& sessionId, Model::Character* character );
    void enterCombat( const std::string& sessionId, Model::Character* character, int roomId );
    void exitCombat( const std::string& sessionId );

    void tick();

    void handleCharacterMessage( const std::string& sessionId, Message::MessageReceiverType type, const Json::Value& payload );

private:
    mutable std::mutex _mutex;
    Model::Location* _location;
    std::unordered_map<std::string, Model::Character*> _characters;
    Core::System::NotificationSystem _notificationSystem;
    Core::System::ActionSystem _actionSystem;
    Core::System::TrainingSystem _trainingSystem;

    std::vector<std::unique_ptr<CombatInstance> > _combatInstances;
    std::unordered_map<std::string, CombatInstance*> _characterCombatCache;
};

} // namespace Core::Instance

#endif // LOCATIONINSTANCE_H
