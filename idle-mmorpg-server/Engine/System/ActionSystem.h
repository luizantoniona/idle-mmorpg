#ifndef ACTIONSYSTEM_H
#define ACTIONSYSTEM_H

#include <Domain/Character/Character.h>
#include <Domain/World/Location/Location.h>
#include <Domain/World/Location/LocationAction.h>

#include "ProgressionSystem.h"

namespace Engine {

class ActionSystem {
public:
    explicit ActionSystem( Domain::Location* location );

    void changeAction( const std::string& sessionId, Domain::Character* character, const Json::Value& payload );

    void process( const std::string& sessionId, Domain::Character* character );

private:
    int computeActionDuration( Domain::Character* character, const Domain::LocationAction& action );
    void regenerativeActionEffect( const std::string& sessionId, Domain::Character* character );
    void gatheringActionEffect( const std::string& sessionId, Domain::Character* character, const Domain::LocationAction& action );

private:
    Domain::Location* _location;
    ProgressionSystem _progressionSystem;
    int _tickRate;
};

} // namespace Engine

#endif // ACTIONSYSTEM_H
