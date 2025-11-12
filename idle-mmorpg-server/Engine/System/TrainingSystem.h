#ifndef TRAININGSYSTEM_H
#define TRAININGSYSTEM_H

#include <string>

#include <Domain/Character/Character.h>
#include <Domain/World/Location/Location.h>

#include "ProgressionSystem.h"

namespace Core::System {

class TrainingSystem {
public:
    explicit TrainingSystem( Domain::Location* location );

    void process( const std::string& sessionId, Domain::Character* character );

private:
    std::vector<Domain::SkillType> combatSkill( Domain::Character* character );

private:
    Domain::Location* _location;
    ProgressionSystem _progressionSystem;
};

} // namespace Core::System

#endif // TRAININGSYSTEM_H
