#include "SpellSystem.h"

#include <iostream>

#include <Commons/Singleton.h>
#include <Core/Manager/SpellManager.h>

#include "NotificationSystem.h"

namespace Core::System {

void SpellSystem::learnSpell( const std::string& sessionId, Model::Character* character, const std::string& spellId ) {
    auto spell = Commons::Singleton<Core::Manager::SpellManager>::instance().spellById( spellId );
    if ( !spell ) {
        std::cerr << "SpellSystem::learnSpell Unknow [SPELL] " << spellId << std::endl;
        return;
    }

    auto& characterSpells = character->spells();
    if ( characterSpells.hasSpell( spellId ) ) {
        std::cout << "SpellSystem::learnSpell Already learned [CHARACTER] " << character->name() << " [SPELL] " << spellId << std::endl;
        return;
    }

    Model::CharacterSpell characterSpell;
    characterSpell.setId( spellId );
    characterSpell.setSpell( spell );

    if ( spell->type() == "healing" ) {
        characterSpells.addHealingSpell( characterSpell );

    } else if ( spell->type() == "attack" ) {
        characterSpells.addAttackSpell( characterSpell );

    } else {
        std::cerr << "SpellSystem::learnSpell Unknow spell type " << spell->type() << std::endl;
    }

    NotificationSystem::notifyCharacterSpells( sessionId, character );
}

} // namespace Core::System
