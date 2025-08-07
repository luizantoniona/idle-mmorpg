#ifndef COMBATSYSTEM_H
#define COMBATSYSTEM_H

#include <string>

#include <Model/Character/Character.h>

#include "NotificationSystem.h"
#include "ProgressionSystem.h"

namespace Core::System {

class CombatSystem {
public:
    explicit CombatSystem( Model::Location* location );

    void process( const std::string& sessionId, Model::Character* character );

private:
    Model::Location* _location;
    NotificationSystem _notificationSystem;
    ProgressionSystem _progressionSystem;
};

} // namespace Core::System

#endif // COMBATSYSTEM_H
