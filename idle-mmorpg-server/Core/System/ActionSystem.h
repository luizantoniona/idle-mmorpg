#ifndef ACTIONSYSTEM_H
#define ACTIONSYSTEM_H

#include <Core/Message/MessageSender.h>
#include <Model/Character/Character.h>
#include <Model/World/Location/Location.h>
#include <Model/World/Location/LocationAction.h>

#include "SkillProgressionSystem.h"

namespace Core::System {

class ActionSystem {
public:
    explicit ActionSystem( Model::Location* location );

    void notifyCharacterActions( const std::string& sessionId, Model::Character* character );
    void notifyCharacterCurrentAction( const std::string& sessionId, Model::Character* character );

    void changeAction( Model::Character* character, const Json::Value& payload );

    void process( const std::string& sessionId, Model::Character* character );

private:
    bool canPerformAction( Model::Character* character, const Model::LocationAction& action );
    int computeActionDuration( Model::Character* character, const Model::LocationAction& action );

private:
    Model::Location* _location;
    Core::Message::MessageSender _sender;
    SkillProgressionSystem _skillProgressionSystem;
};

} // namespace Core::System

#endif // ACTIONSYSTEM_H
