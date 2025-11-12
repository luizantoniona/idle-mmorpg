#ifndef LOCATIONINSTANCE_H
#define LOCATIONINSTANCE_H

#include <mutex>
#include <string>
#include <unordered_map>

#include <Core/Message/MessageReceiverType.h>
#include <Core/System/ActionSystem.h>
#include <Core/System/TrainingSystem.h>
#include <Domain/Character/Character.h>
#include <Domain/World/Location/Location.h>

#include "CombatInstance.h"

namespace Engine {

class LocationInstance {
public:
    explicit LocationInstance( Domain::Location* location );

    Domain::Location* location();

    bool addCharacter( const std::string& sessionId, Domain::Character* character );
    void removeCharacter( const std::string& sessionId );

    void changeStructure( const std::string& sessionId, Domain::Character* character, const Json::Value& payload );

    void createCombat( const std::string& sessionId, Domain::Character* character );
    void enterCombat( const std::string& sessionId, Domain::Character* character, const std::string& roomId );
    void exitCombat( const std::string& sessionId );

    void tick();

    void handleCharacterMessage( const std::string& sessionId, Message::MessageReceiverType type, const Json::Value& payload );

private:
    mutable std::mutex _mutex;
    Domain::Location* _location;
    std::unordered_map<std::string, Domain::Character*> _characters;
    Core::System::ActionSystem _actionSystem;
    Core::System::TrainingSystem _trainingSystem;

    std::vector<std::unique_ptr<CombatInstance> > _combatInstances;
    std::unordered_map<std::string, CombatInstance*> _characterCombatCache;
};

} // namespace Engine

#endif // LOCATIONINSTANCE_H
