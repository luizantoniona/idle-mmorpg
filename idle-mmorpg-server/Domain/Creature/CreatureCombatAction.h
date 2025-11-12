#ifndef CREATURECOMBATACTION_H
#define CREATURECOMBATACTION_H

#include <json/json.h>

namespace Domain {

class CreatureCombatAction {
public:
    CreatureCombatAction();

    Json::Value toJson();

    int duration() const;
    void setDuration( int duration );

    int counter() const;
    void setCounter( int counter );

private:
    int _duration;
    int _counter;
};

} // namespace Domain

#endif // CREATURECOMBATACTION_H
