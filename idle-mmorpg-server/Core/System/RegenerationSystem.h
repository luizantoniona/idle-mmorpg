#ifndef REGENERATIONSYSTEM_H
#define REGENERATIONSYSTEM_H

#include <Model/Character/Character.h>

namespace Core::System {

class RegenerationSystem {
public:
    static void computeRegeneration( const std::string& sessionId, Model::Character* character );
    static void computeSpellsCooldown( const std::string& sessionId, Model::Character* character );

    static void castHealingSpell( const std::string& sessionId, Model::Character* character, const std::string& spellId );
};

} // namespace Core::System

#endif // REGENERATIONSYSTEM_H
