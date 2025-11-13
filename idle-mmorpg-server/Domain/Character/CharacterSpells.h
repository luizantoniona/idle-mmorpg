#ifndef CHARACTERSPELLS_H
#define CHARACTERSPELLS_H

#include <json/json.h>

#include "CharacterSpell.h"

namespace Domain {

class CharacterSpells {
public:
    CharacterSpells();

    Json::Value toJson();

    std::vector<CharacterSpell>& healingSpells();
    void setHealingSpells( const std::vector<CharacterSpell>& healingSpells );
    void addHealingSpell( const CharacterSpell& healingSpell );

    std::vector<CharacterSpell>& attackSpells();
    void setAttackSpells( const std::vector<CharacterSpell>& attackSpells );
    void addAttackSpell( const CharacterSpell& attackSpell );

    bool hasSpell( const std::string& spellId ) const;

    CharacterSpell* attackSpell( const std::string& spellId );
    CharacterSpell* healingSpell( const std::string& spellId );

private:
    std::vector<CharacterSpell> _healingSpells;
    std::vector<CharacterSpell> _attackSpells;
};

} // namespace Domain

#endif // CHARACTERSPELLS_H
