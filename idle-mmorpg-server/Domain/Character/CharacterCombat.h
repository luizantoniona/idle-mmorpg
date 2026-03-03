#ifndef CHARACTERCOMBAT_H
#define CHARACTERCOMBAT_H

#include <json/json.h>

namespace Domain {

class CharacterCombat {
public:
    CharacterCombat();

    Json::Value toJson();

    double attack() const;
    void setAttack( double attack );

    int attackCounter() const;
    void setAttackCounter( int attackCounter );

    int attackDuration() const;
    void setAttackDuration( int attackDuration );

private:
    double _attack;

    int _attackCounter;
    int _attackDuration;
};

} // namespace Domain

#endif // CHARACTERCOMBAT_H
