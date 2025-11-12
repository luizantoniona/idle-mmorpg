#ifndef EFFECTSYSTEM_H
#define EFFECTSYSTEM_H

#include <Domain/Character/Character.h>

namespace Core::System {

class EffectSystem {
public:
    static void processEffects( const std::string& sessionId, Domain::Character* character );
};

} // namespace Core::System

#endif // EFFECTSYSTEM_H
