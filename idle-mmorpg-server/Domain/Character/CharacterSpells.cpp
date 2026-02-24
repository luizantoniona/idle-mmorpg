#include "CharacterSpells.h"

namespace Domain {

CharacterSpells::CharacterSpells() {}

Json::Value CharacterSpells::toJson() {
    Json::Value values( Json::arrayValue );
    for ( const auto& spell : _spells ) {
        values.append( spell.toJson() );
    }

    Json::Value spells;
    spells[ "spells" ] = values;
    return spells;
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
