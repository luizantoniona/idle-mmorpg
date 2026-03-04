#include "CharacterEvent.h"

namespace Engine {

CharacterEvent::CharacterEvent( CharacterEventType type, const Json::Value& payload ) :
    _type( type ),
    _payload( payload ) {
}

CharacterEventType CharacterEvent::type() const {
    return _type;
}

const Json::Value& CharacterEvent::payload() const {
    return _payload;
}

} // namespace Engine
