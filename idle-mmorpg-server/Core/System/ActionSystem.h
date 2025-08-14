#ifndef ACTIONSYSTEM_H
#define ACTIONSYSTEM_H

#include <Core/Message/MessageSender.h>
#include <Model/Character/Character.h>
#include <Model/World/Location/Location.h>
#include <Model/World/Location/LocationAction.h>

#include "ProgressionSystem.h"

namespace Core::System {

class ActionSystem {
public:
    explicit ActionSystem( Model::Location* location );

    void changeAction( const std::string& sessionId, Model::Character* character, const Json::Value& payload );
    void changeStructure( const std::string& sessionId, Model::Character* character, const Json::Value& payload );

    void process( const std::string& sessionId, Model::Character* character );

private:
    int computeActionDuration( Model::Character* character, const Model::LocationAction& action );
    void regenerativeActionEffect( Model::Character* character );

private:
    Model::Location* _location;
    ProgressionSystem _progressionSystem;
};

} // namespace Core::System

#endif // ACTIONSYSTEM_H
