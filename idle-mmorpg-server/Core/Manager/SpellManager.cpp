#include "SpellManager.h"

#include <Core/Factory/Spell/SpellFactory.h>

namespace Core::Manager {

SpellManager::SpellManager() :
    _spells() {
}

void SpellManager::initialize( const std::string& spellsPath ) {
    _spells = Core::Factory::SpellFactory::createSpells( spellsPath );
}

Model::Spell* SpellManager::spell( const std::string& spellId ) {
    auto it = _spells.find( spellId );
    if ( it != _spells.end() ) {
        return it->second.get();
    }

    return nullptr;
}

} // namespace Core::Manager
