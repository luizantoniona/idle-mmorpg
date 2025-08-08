#ifndef CHARACTERCOMBATATTRIBUTES_H
#define CHARACTERCOMBATATTRIBUTES_H

#include <json/json.h>

namespace Model {

class CharacterCombatAttributes {
public:
    CharacterCombatAttributes();

    Json::Value toJson() const;

    double attack() const;
    double accuracy() const;
    double defense() const;
    double speed() const;
    double evasion() const;
    double criticalChance() const;
    double criticalMultiplier() const;

    double baseAttack() const;
    void setBaseAttack( double baseAttack );

    double baseAccuracy() const;
    void setBaseAccuracy( double baseAccuracy );

    double baseDefense() const;
    void setBaseDefense( double baseDefense );

    double baseSpeed() const;
    void setBaseSpeed( double baseSpeed );

    double baseEvasion() const;
    void setBaseEvasion( double baseEvasion );

    double baseCriticalChance() const;
    void setBaseCriticalChance( double baseCriticalChance );

    double baseCriticalMultiplier() const;
    void setBaseCriticalMultiplier( double baseCriticalMultiplier );

    void modifyAttack( double modifier );
    void modifyAccuracy( double modifier );
    void modifyDefense( double modifier );
    void modifySpeed( double modifier );
    void modifyEvasion( double modifier );
    void modifyCriticalChance( double modifier );
    void modifyCriticalMultiplier( double modifier );

private:
    double _baseAttack;
    double _baseAccuracy;
    double _baseDefense;
    double _baseSpeed;
    double _baseEvasion;
    double _baseCriticalChance;
    double _baseCriticalMultiplier;

    double _modifierAttack;
    double _modifierAccuracy;
    double _modifierDefense;
    double _modifierSpeed;
    double _modifierEvasion;
    double _modifierCriticalChance;
    double _modifierCriticalMultiplier;
};

} // namespace Model

#endif // CHARACTERCOMBATATTRIBUTES_H
