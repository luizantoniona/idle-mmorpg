#ifndef CHARACTERCOMBATACTION_H
#define CHARACTERCOMBATACTION_H

#include <json/json.h>

namespace Model {

class CharacterCombatAction {
public:
    CharacterCombatAction();

    Json::Value toJson();

    int duration() const;
    void setDuration( int duration );

    int counter() const;
    void setCounter( int counter );

private:
    int _duration;
    int _counter;
};

} // namespace Model

#endif // CHARACTERCOMBATACTION_H
