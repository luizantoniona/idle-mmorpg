#ifndef CHARACTEREVENT_H
#define CHARACTEREVENT_H

#include <json/json.h>

#include "CharacterEventType.h"

namespace Engine {

class CharacterEvent {
public:
    CharacterEvent( CharacterEventType type, const Json::Value& payload );

    CharacterEventType type() const;
    const Json::Value& payload() const;

private:
    CharacterEventType _type;
    Json::Value _payload;
};

} // namespace Engine

#endif // CHARACTEREVENT_H
