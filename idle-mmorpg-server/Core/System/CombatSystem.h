#ifndef COMBATSYSTEM_H
#define COMBATSYSTEM_H

#include <string>

#include <Model/Character/Character.h>

namespace Core::System {

class CombatSystem {
public:
    CombatSystem();

    void process( const std::string& sessionId, Model::Character* character );
};

} // namespace Core::System

#endif // COMBATSYSTEM_H
