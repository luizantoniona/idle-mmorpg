#ifndef TRAININGSYSTEM_H
#define TRAININGSYSTEM_H

#include <string>

#include <Model/Character/Character.h>

#include "ProgressionSystem.h"

namespace Core::System {

class TrainingSystem {
public:
    explicit TrainingSystem( Model::Location* location );

    void process( const std::string& sessionId, Model::Character* character );

private:
    std::string combatSkill( Model::Character* character );

private:
    Model::Location* _location;
    ProgressionSystem _progressionSystem;
};

} // namespace Core::System

#endif // TRAININGSYSTEM_H
