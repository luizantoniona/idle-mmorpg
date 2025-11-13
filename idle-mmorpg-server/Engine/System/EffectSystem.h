#ifndef EFFECTSYSTEM_H
#define EFFECTSYSTEM_H

#include <Domain/Character/Character.h>

namespace Engine {

class EffectSystem {
public:
    static void processEffects( const std::string& sessionId, Domain::Character* character );
};

} // namespace Engine

#endif // EFFECTSYSTEM_H
