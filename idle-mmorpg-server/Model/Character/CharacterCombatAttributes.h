#ifndef CHARACTERCOMBATATTRIBUTES_H
#define CHARACTERCOMBATATTRIBUTES_H

namespace Model {

class CharacterCombatAttributes {
public:
    CharacterCombatAttributes();

    double attack() const;
    void setAttack( double attack );

    double defense() const;
    void setDefense( double defense );

    double attackSpeed() const;
    void setAttackSpeed( double attackSpeed );

    double criticalChance() const;
    void setCriticalChance( double criticalChance );

    double criticalMultiplier() const;
    void setCriticalMultiplier( double criticalMultiplier );

    void clear();

private:
    double _attack;
    double _defense;
    double _attackSpeed;
    double _criticalChance;
    double _criticalMultiplier;
};

} // namespace Model

#endif // CHARACTERCOMBATATTRIBUTES_H
