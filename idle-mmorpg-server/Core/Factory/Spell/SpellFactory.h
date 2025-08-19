#ifndef SPELLFACTORY_H
#define SPELLFACTORY_H

#include <memory>
#include <string>
#include <unordered_map>

#include <Model/Spell/Spell.h>

namespace Core::Factory {

class SpellFactory {
public:
    static std::unordered_map<std::string, std::unique_ptr<Model::Spell>> createSpells( const std::string& spellsPath );

private:
    static std::unique_ptr<Model::Spell> createSpell( const std::string& spellPath );
};

} // namespace Core::Factory

#endif // SPELLFACTORY_H
