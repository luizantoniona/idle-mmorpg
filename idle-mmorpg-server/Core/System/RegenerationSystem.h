#ifndef REGENERATIONSYSTEM_H
#define REGENERATIONSYSTEM_H

#include <Model/Character/Character.h>

namespace Core::System {

class RegenerationSystem {
public:
    static void computeRegeneration( const std::string& sessionId, Model::Character* character );
};

} // namespace Core::System

#endif // REGENERATIONSYSTEM_H
