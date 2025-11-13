#ifndef CHARACTERSKILLS_H
#define CHARACTERSKILLS_H

#include <json/json.h>

#include "CharacterSkill.h"

namespace Domain {

class CharacterSkills {
public:
    CharacterSkills();

    Json::Value toJson();

    std::vector<CharacterSkill>& skills();

    CharacterSkill* skill( SkillType type );
    void addSkill( CharacterSkill skill );

    int skillLevel( SkillType type );

    void clear();

private:
    std::vector<CharacterSkill> _skills;
};

} // namespace Domain

#endif // CHARACTERSKILLS_H
