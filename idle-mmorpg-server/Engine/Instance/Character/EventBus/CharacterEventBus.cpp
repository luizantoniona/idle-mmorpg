#include "CharacterEventBus.h"

namespace Engine {

void CharacterEventBus::subscribe( CharacterEventType type, Listener listener ) {
    _listeners[ type ].push_back( listener );
}

void CharacterEventBus::publish( const CharacterEvent& event ) {
    auto it = _listeners.find( event.type() );
    if ( it == _listeners.end() ) {
        return;
    }

    for ( auto& listener : it->second ) {
        listener( event );
    }
}

} // namespace Engine
