#ifndef EFFECTSYSTEM_H
#define EFFECTSYSTEM_H

#include <Model/Character/Character.h>

namespace Core::System {

class EffectSystem {
public:
    static void computeEffects( const std::string& sessionId, Model::Character* character );
};

} // namespace Core::System

#endif // EFFECTSYSTEM_H
