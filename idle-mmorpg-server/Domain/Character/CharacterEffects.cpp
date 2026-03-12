#include "CharacterEffects.h"

#include <algorithm>

namespace Domain {

CharacterEffects::CharacterEffects() {}

Json::Value CharacterEffects::toJson() {
    Json::Value values;
    for ( auto& effect : effects() ) {
        values.append( effect.toJson() );
    }

    Json::Value effects;
    effects[ "effects" ] = values;
    return effects;
}

std::vector<CharacterEffect>& CharacterEffects::effects() {
    return _effects;
}

void CharacterEffects::addEffect( CharacterEffect effect ) {
    for ( auto& oldEffect : _effects ) {
        if ( oldEffect.source() == effect.source() ) {
            oldEffect.setDuration( oldEffect.duration() + effect.duration() );
            return;
        }
    }

    _effects.push_back( effect );
}

void CharacterEffects::removeEffect( const CharacterEffect& effect ) {
    _effects.erase(
        std::remove_if( _effects.begin(), _effects.end(), [ &effect ]( const CharacterEffect& e ) {
            return e.source() == effect.source();
        } ),
        _effects.end() );
}

} // namespace Domain
