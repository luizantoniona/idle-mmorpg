#ifndef SPELLSYSTEM_H
#define SPELLSYSTEM_H

#include <string>

#include <Domain/Character/Character.h>

namespace Core::System {

class SpellSystem {
public:
    static void learnSpell( const std::string& sessionId, Domain::Character* character, const std::string& spellId );
};

} // namespace Core::System

#endif // SPELLSYSTEM_H
