#ifndef CHARACTEREFFECTS_H
#define CHARACTEREFFECTS_H

#include <vector>

#include <json/json.h>

#include "CharacterEffect.h"

namespace Domain {

class CharacterEffects {
public:
    CharacterEffects();

    Json::Value toJson();

    std::vector<CharacterEffect>& effects();
    void addEffect( CharacterEffect effect );
    void removeEffect( const CharacterEffect& effect );

private:
    std::vector<CharacterEffect> _effects;
};

} // namespace Domain

#endif // CHARACTEREFFECTS_H
