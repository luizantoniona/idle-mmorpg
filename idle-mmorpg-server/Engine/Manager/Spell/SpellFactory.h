#ifndef SPELLFACTORY_H
#define SPELLFACTORY_H

#include <memory>
#include <string>
#include <unordered_map>

#include <Domain/Spell/Spell.h>

namespace Engine {

class SpellFactory {
public:
    static std::unordered_map<std::string, std::unique_ptr<Domain::Spell>> createSpells( const std::string& spellsPath );

private:
    static std::unique_ptr<Domain::Spell> createSpell( const std::string& spellPath );
};

} // namespace Engine

#endif // SPELLFACTORY_H
