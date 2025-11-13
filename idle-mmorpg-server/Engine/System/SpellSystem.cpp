#include "SpellSystem.h"

#include <iostream>

#include <Engine/Manager/Spell/SpellManager.h>
#include <Shared/Commons/Singleton.h>

#include "NotificationSystem.h"

namespace Engine {

void SpellSystem::learnSpell( const std::string& sessionId, Domain::Character* character, const std::string& spellId ) {
    auto spell = Commons::Singleton<Engine::SpellManager>::instance().spellById( spellId );
    if ( !spell ) {
        std::cerr << "SpellSystem::learnSpell Unknow [SPELL] " << spellId << std::endl;
        return;
    }

    auto& characterSpells = character->spells();
    if ( characterSpells.hasSpell( spellId ) ) {
        std::cout << "SpellSystem::learnSpell Already learned [CHARACTER] " << character->name() << " [SPELL] " << spellId << std::endl;
        return;
    }

    Domain::CharacterSpell characterSpell;
    characterSpell.setId( spellId );
    characterSpell.setSpell( spell );
    characterSpell.setCount( spell->cooldown() );

    if ( spell->type() == "healing" ) {
        characterSpells.addHealingSpell( characterSpell );

    } else if ( spell->type() == "attack" ) {
        characterSpells.addAttackSpell( characterSpell );

    } else {
        std::cerr << "SpellSystem::learnSpell Unknow spell type " << spell->type() << std::endl;
    }

    NotificationSystem::notifyCharacterSpells( sessionId, character );
}

} // namespace Engine
