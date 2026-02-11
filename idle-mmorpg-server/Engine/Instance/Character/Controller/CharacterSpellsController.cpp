#include "CharacterSpellsController.h"

namespace Engine {

CharacterSpellsController::CharacterSpellsController( Domain::CharacterSpells& spells, Manager::SpellManager& spellManager ) :
    _spells( spells ),
    _spellManager( spellManager ) {
}

void CharacterSpellsController::onEnterWorld() {
    for ( auto& spell : _spells.spells() ) {
        Domain::Spell* resolved = _spellManager.spellById( spell.id() );
        if ( !resolved ) {
            continue;
        }

        spell.setSpell( resolved );
        spell.setCount( resolved->cooldown() );
    }
}

void CharacterSpellsController::onExitWorld() {
}

} // namespace Engine
