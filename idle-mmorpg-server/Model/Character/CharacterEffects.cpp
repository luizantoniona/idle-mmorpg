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
    _effects.push_back( effect );
}

} // namespace Model
