#ifndef CHARACTERSKILLS_H
#define CHARACTERSKILLS_H

#include <string>

#include <json/json.h>

#include "CharacterSkill.h"

namespace Model {

class CharacterSkills {
public:
    CharacterSkills();

    Json::Value toJson();

    std::vector<CharacterSkill>& skills();

    CharacterSkill* skill( const std::string& idSkill );
    void addSkill( CharacterSkill skill );

private:
    std::vector<CharacterSkill> _skills;
};

} // namespace Model

#endif // CHARACTERSKILLS_H
