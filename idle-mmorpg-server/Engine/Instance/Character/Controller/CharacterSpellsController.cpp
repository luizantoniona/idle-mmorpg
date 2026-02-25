#include "CharacterSpellsController.h"

namespace Engine {

CharacterSpellsController::CharacterSpellsController( std::function<void( MessageSenderType, const Json::Value& )> sendMessage,
                                                      Domain::CharacterSpells& spells,
                                                      Manager::SpellManager& spellManager ) :
    CharacterController( sendMessage ),
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

    sendMessage( MessageSenderType::CHARACTER_SPELLS, _spells.toJson() );
}

void CharacterSpellsController::onLeaveWorld() {
}

void CharacterSpellsController::onTick() {
}

} // namespace Engine
