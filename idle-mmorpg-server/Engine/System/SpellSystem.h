#ifndef SPELLSYSTEM_H
#define SPELLSYSTEM_H

#include <string>

#include <Domain/Character/Character.h>

namespace Engine {

class SpellSystem {
public:
    static void learnSpell( const std::string& sessionId, Domain::Character* character, const std::string& spellId );
};

} // namespace Engine

#endif // SPELLSYSTEM_H
