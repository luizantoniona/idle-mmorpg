#include "CharacterSpells.h"

namespace Domain {

CharacterSpells::CharacterSpells() {}

Json::Value CharacterSpells::toJson() {
    Json::Value root;

    Json::Value healing( Json::arrayValue );
    for ( const auto& spell : _healingSpells ) {
        healing.append( spell.toJson() );
    }
    root[ "healing" ] = healing;

    Json::Value attack( Json::arrayValue );
    for ( const auto& spell : _attackSpells ) {
        attack.append( spell.toJson() );
    }
    root[ "attack" ] = attack;

    return root;
}

std::vector<CharacterSpell>& CharacterSpells::healingSpells() {
    return _healingSpells;
}

void CharacterSpells::setHealingSpells( const std::vector<CharacterSpell>& healingSpells ) {
    _healingSpells = healingSpells;
}

void CharacterSpells::addHealingSpell( const CharacterSpell& healingSpell ) {
    _healingSpells.push_back( healingSpell );
}

std::vector<CharacterSpell>& CharacterSpells::attackSpells() {
    return _attackSpells;
}

void CharacterSpells::setAttackSpells( const std::vector<CharacterSpell>& attackSpells ) {
    _attackSpells = attackSpells;
}

void CharacterSpells::addAttackSpell( const CharacterSpell& attackSpell ) {
    _attackSpells.push_back( attackSpell );
}

bool CharacterSpells::hasSpell( const std::string& spellId ) const {
    for ( const auto& spell : _healingSpells ) {
        if ( spell.id() == spellId ) {
            return true;
        }
    }

    for ( const auto& spell : _attackSpells ) {
        if ( spell.id() == spellId ) {
            return true;
        }
    }

    return false;
}

CharacterSpell* CharacterSpells::attackSpell( const std::string& spellId ) {
    for ( auto& spell : _attackSpells ) {
        if ( spell.id() == spellId ) {
            return &spell;
        }
    }

    return nullptr;
}

CharacterSpell* CharacterSpells::healingSpell( const std::string& spellId ) {
    for ( auto& spell : _healingSpells ) {
        if ( spell.id() == spellId ) {
            return &spell;
        }
    }

    return nullptr;
}

} // namespace Domain
