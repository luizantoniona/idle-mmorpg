#include "CharacterSpellsController.h"

namespace Engine {

CharacterSpellsController::CharacterSpellsController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                      Domain::CharacterSpells& spells,
                                                      Manager::SpellManager& spellManager ) :
    CharacterController( eventBus, messageSender ),
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

    _messageSender.sendMessage( MessageSenderType::CHARACTER_SPELLS, _spells.toJson() );
}

void CharacterSpellsController::onLeaveWorld() {
}

void CharacterSpellsController::onTick() {
}

} // namespace Engine
