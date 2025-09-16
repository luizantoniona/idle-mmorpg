#include "CharacterEffects.h"

namespace Model {

CharacterEffects::CharacterEffects() {
}

Json::Value CharacterEffects::toJson() {
    Json::Value root;
    for ( auto& effect : effects() ) {
        root[ "effects" ].append( effect.toJson() );
    }
    return root;
}

std::vector<CharacterEffect>& CharacterEffects::effects() {
    return _effects;
}

void CharacterEffects::addEffect( CharacterEffect effect ) {
    for ( auto& oldEffect : _effects ) {
        if ( oldEffect.id() == effect.id() && oldEffect.type() == effect.type() && oldEffect.category() == effect.category() ) {
            oldEffect.setDuration( oldEffect.duration() + effect.duration() );
            return;
        }
    }

    _effects.push_back( effect );
}

void CharacterEffects::removeEffect( const CharacterEffect& effect ) {
    _effects.erase(
        std::remove_if( _effects.begin(), _effects.end(), [ &effect ]( const CharacterEffect& e ) {
            return e.id() == effect.id() && e.type() == effect.type() && e.category() == effect.category();
        } ),
        _effects.end() );
}

} // namespace Model
