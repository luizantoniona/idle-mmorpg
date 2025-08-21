#ifndef CHARACTERSPELLS_H
#define CHARACTERSPELLS_H

#include <json/json.h>

#include "CharacterSpell.h"

namespace Model {

class CharacterSpells {
public:
    CharacterSpells();

    Json::Value toJson();

    std::vector<CharacterSpell> healingSpells() const;
    void setHealingSpells( const std::vector<CharacterSpell>& healingSpells );
    void addHealingSpell( const CharacterSpell& healingSpell );

    std::vector<CharacterSpell> attackSpells() const;
    void setAttackSpells( const std::vector<CharacterSpell>& attackSpells );
    void addAttackSpell( const CharacterSpell& attackSpell );

    bool hasSpell( const std::string& spellId ) const;

private:
    std::vector<CharacterSpell> _healingSpells;
    std::vector<CharacterSpell> _attackSpells;
};

} // namespace Model

#endif // CHARACTERSPELLS_H
