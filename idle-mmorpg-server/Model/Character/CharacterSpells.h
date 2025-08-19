#ifndef CHARACTERSPELLS_H
#define CHARACTERSPELLS_H

#include <string>

#include <json/json.h>

namespace Model {

class CharacterSpells {
public:
    CharacterSpells();

    Json::Value toJson();
};

} // namespace Model

#endif // CHARACTERSPELLS_H
