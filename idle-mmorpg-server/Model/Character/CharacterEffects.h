#ifndef CHARACTEREFFECTS_H
#define CHARACTEREFFECTS_H

#include <vector>

#include <json/json.h>

#include "CharacterEffect.h"

namespace Model {

class CharacterEffects {
public:
    CharacterEffects();

    Json::Value toJson();

    std::vector<CharacterEffect>& effects();
    void addEffect( CharacterEffect effect );

private:
    std::vector<CharacterEffect> _effects;
};

} // namespace Model

#endif // CHARACTEREFFECTS_H
