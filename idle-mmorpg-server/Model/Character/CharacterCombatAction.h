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

    int regenDuration() const;
    void setRegenDuration( int regenDuration );
    int regenCounter() const;
    void setRegenCounter( int regenCounter );

private:
    int _duration;
    int _counter;

    int _regenDuration;
    int _regenCounter;
};

} // namespace Model

#endif // CHARACTERCOMBATACTION_H
