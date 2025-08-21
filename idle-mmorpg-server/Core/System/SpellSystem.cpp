#include "SpellSystem.h"

#include <Commons/Singleton.h>
#include <Core/Manager/SpellManager.h>

#include "NotificationSystem.h"

namespace Core::System {

void SpellSystem::learnSpell( const std::string& sessionId, Model::Character* character, const std::string& spellId ) {
    auto spell = Commons::Singleton<Core::Manager::SpellManager>::instance().spellById( spellId );
    if ( !spell ) {
        return;
    }

    auto& characterSpells = character->spells();
    if ( characterSpells.hasSpell( spellId ) ) {
        return;
    }

    Model::CharacterSpell characterSpell;
    characterSpell.setId( spellId );
    characterSpell.setSpell( spell );

    if ( spell->type() == "healing" ) {
        characterSpells.addHealingSpell( characterSpell );

    } else if ( spell->type() == "attack" ) {
        characterSpells.addAttackSpell( characterSpell );
    }

    NotificationSystem::notifyCharacterSpells( sessionId, character );
}

} // namespace Core::System
