#ifndef REGENERATIONSYSTEM_H
#define REGENERATIONSYSTEM_H

#include <Model/Character/Character.h>

namespace Core::System {

class RegenerationSystem {
public:
    static void processRegeneration( const std::string& sessionId, Model::Character* character );
    static void computeRegeneration( const std::string& sessionId, Model::Character* character, double baseRegenerationValue = 1.0 );

    static void processSpellsCooldown( const std::string& sessionId, Model::Character* character );

    static void castHealingSpell( const std::string& sessionId, Model::Character* character, const std::string& spellId );
};

} // namespace Core::System

#endif // REGENERATIONSYSTEM_H
