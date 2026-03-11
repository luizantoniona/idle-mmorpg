#ifndef CHARACTERCOMBAT_H
#define CHARACTERCOMBAT_H

#include <json/json.h>

namespace Domain {

class CharacterCombat {
public:
    CharacterCombat();

    Json::Value toJson();

    bool isInCombat() const;
    void setIsInCombat( bool isInCombat );

    double attack() const;
    void setAttack( double attack );

    double defense() const;
    void setDefense( double defense );

    int attackCounter() const;
    void setAttackCounter( int attackCounter );

    int attackDuration() const;
    void setAttackDuration( int attackDuration );

    void clearAttributes();

private:
    bool _isInCombat;

    double _attack;
    double _defense;

    int _attackCounter;
    int _attackDuration;
};

} // namespace Domain

#endif // CHARACTERCOMBAT_H
