#ifndef CHARACTERCOMBATATTRIBUTES_H
#define CHARACTERCOMBATATTRIBUTES_H

#include <json/json.h>

namespace Model {

class CharacterCombatAttributes {
public:
    CharacterCombatAttributes();

    Json::Value toJson() const;

    double attack() const;
    void setAttack( double attack );
    void modifyAttack( double modifier );

    double attackSpeed() const;
    void setAttackSpeed( double attackSpeed );
    void modifyAttackSpeed( double modifier );

    double defense() const;
    void setDefense( double attack );
    void modifyDefense( double modifier );

    void clear();

private:
    double _attack;
    double _attackSpeed;
    double _defense;
};

} // namespace Model

#endif // CHARACTERCOMBATATTRIBUTES_H
