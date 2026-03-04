#ifndef CHARACTERSPELLS_H
#define CHARACTERSPELLS_H

#include <json/json.h>

#include "CharacterSpell.h"

namespace Domain {

class CharacterSpells {
public:
    CharacterSpells();

    Json::Value toJson();

    std::vector<CharacterSpell>& spells();
    void setSpells( const std::vector<CharacterSpell>& spells );
    void addSpell( const CharacterSpell& spell );

private:
    std::vector<CharacterSpell> _spells;
};

} // namespace Domain

#endif // CHARACTERSPELLS_H
