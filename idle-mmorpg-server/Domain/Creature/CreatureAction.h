#ifndef CREATUREACTION_H
#define CREATUREACTION_H

#include <json/json.h>

namespace Domain {

class CreatureAction {
public:
    CreatureAction();

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

#endif // CREATUREACTION_H
