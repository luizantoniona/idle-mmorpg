#ifndef SPELLMANAGER_H
#define SPELLMANAGER_H

#include <memory>
#include <string>
#include <unordered_map>

#include <Domain/Spell/Spell.h>

namespace Manager {

class SpellManager {
public:
    SpellManager();

    void initialize( const std::string& spellsPath );

    Domain::Spell* spellById( const std::string& spellId );

private:
    std::unordered_map<std::string, std::unique_ptr<Domain::Spell> > _spells;
};

} // namespace Manager

#endif // SPELLMANAGER_H
