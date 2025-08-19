#ifndef SPELLMANAGER_H
#define SPELLMANAGER_H

#include <memory>
#include <string>
#include <unordered_map>

#include <Model/Spell/Spell.h>

namespace Core::Manager {

class SpellManager {
public:
    SpellManager();

    void initialize( const std::string& spellsPath );

    Model::Spell* spell( const std::string& spellId );

private:
    std::unordered_map<std::string, std::unique_ptr<Model::Spell>> _spells;
};

} // namespace Core::Manager

#endif // SPELLMANAGER_H
