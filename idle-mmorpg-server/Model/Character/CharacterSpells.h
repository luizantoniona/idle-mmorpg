#ifndef CHARACTERSPELLS_H
#define CHARACTERSPELLS_H

#include <string>

#include <json/json.h>

#include "CharacterSpell.h"

namespace Model {

class CharacterSpells {
public:
    CharacterSpells();

    Json::Value toJson();

private:
    std::vector<CharacterSpell> _healingSpells;
    std::vector<CharacterSpell> _attackSpells;
};

} // namespace Model

#endif // CHARACTERSPELLS_H
