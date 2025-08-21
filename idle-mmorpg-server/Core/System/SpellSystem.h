#ifndef SPELLSYSTEM_H
#define SPELLSYSTEM_H

#include <string>

#include <Model/Character/Character.h>

namespace Core::System {

class SpellSystem {
public:
    static void learnSpell( const std::string& sessionId, Model::Character* character, const std::string& spellId );
};

} // namespace Core::System

#endif // SPELLSYSTEM_H
