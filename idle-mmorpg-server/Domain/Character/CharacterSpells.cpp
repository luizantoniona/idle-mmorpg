#include "CharacterSpells.h"

namespace Domain {

CharacterSpells::CharacterSpells() {}

Json::Value CharacterSpells::toJson() {
    Json::Value root;

    Json::Value spells( Json::arrayValue );
    for ( const auto& spell : _spells ) {
        spells.append( spell.toJson() );
    }
    root[ "spells" ] = spells;

    return root;
}

std::vector<CharacterSpell>& CharacterSpells::spells() {
    return _spells;
}

void CharacterSpells::setSpells( const std::vector<CharacterSpell>& spells ) {
    _spells = spells;
}

void CharacterSpells::addSpell( const CharacterSpell& spell ) {
    _spells.push_back( spell );
}

} // namespace Domain
