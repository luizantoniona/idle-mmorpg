#include "SpellManager.h"

#include "SpellFactory.h"

namespace Manager {

SpellManager::SpellManager() :
    _spells() {}

void SpellManager::initialize( const std::string& spellsPath ) {
    _spells = SpellFactory::createSpells( spellsPath );
}

Domain::Spell* SpellManager::spellById( const std::string& spellId ) {
    auto it = _spells.find( spellId );
    if ( it != _spells.end() ) {
        return it->second.get();
    }

    return nullptr;
}

} // namespace Manager
