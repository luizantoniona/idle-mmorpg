#include "CharacterSpellsController.h"

namespace Engine {

CharacterSpellsController::CharacterSpellsController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                      Domain::Character& character,
                                                      Manager::SpellManager& spellManager ) :
    CharacterController( eventBus, messageSender ),
    _characterSpells( character.spells() ),
    _spellManager( spellManager ) {
}

void CharacterSpellsController::onEnterWorld() {
    for ( auto& spell : _characterSpells.spells() ) {
        Domain::Spell* resolved = _spellManager.spellById( spell.id() );
        if ( !resolved ) {
            continue;
        }

        spell.setSpell( resolved );
        spell.setCount( resolved->cooldown() );
    }

    _messageSender.sendMessage( MessageSenderType::CHARACTER_SPELLS, _characterSpells.toJson() );
}

void CharacterSpellsController::onLeaveWorld() {
}

void CharacterSpellsController::onTick() {
}

} // namespace Engine
