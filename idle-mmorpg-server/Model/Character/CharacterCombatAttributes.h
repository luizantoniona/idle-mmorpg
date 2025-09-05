#ifndef CHARACTERCOMBATATTRIBUTES_H
#define CHARACTERCOMBATATTRIBUTES_H

namespace Model {

class CharacterCombatAttributes {
public:
    CharacterCombatAttributes();

    double attack() const;
    void setAttack( double attack );

    double attackSpeed() const;
    void setAttackSpeed( double attackSpeed );

    double defense() const;
    void setDefense( double attack );

    void clear();

private:
    double _attack;
    double _attackSpeed;
    double _defense;
};

} // namespace Model

#endif // CHARACTERCOMBATATTRIBUTES_H
