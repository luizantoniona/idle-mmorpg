#ifndef ACTIONSYSTEM_H
#define ACTIONSYSTEM_H

#include <Model/Character/Character.h>
#include <Model/World/Location/LocationAction.h>

namespace Core::System {

class ActionSystem {
public:
    ActionSystem();

    bool canPerformAction( Model::Character* character, const Model::LocationAction& action );

    void startAction( Model::Character* character, const Model::LocationAction& action );
    void endAction( Model::Character* character );

    // void tick( Model::Character* character, std::function<void( const Json::Value& )> onFinishedCallback );
};

} // namespace Core::System

#endif // ACTIONSYSTEM_H
