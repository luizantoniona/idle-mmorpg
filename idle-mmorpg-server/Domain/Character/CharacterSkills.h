#ifndef CHARACTERSKILLS_H
#define CHARACTERSKILLS_H

#include <unordered_map>

#include <json/json.h>

#include "CharacterSkill.h"

namespace Domain {

class CharacterSkills {
public:
    CharacterSkills();

    Json::Value toJson();

    std::unordered_map<SkillType, CharacterSkill>& skills();

    CharacterSkill* skill( SkillType type );
    void addSkill( const CharacterSkill& skill );

    int skillLevel( SkillType type ) const;

    void clear();

private:
    std::unordered_map<SkillType, CharacterSkill> _skills;
};

} // namespace Domain

#endif // CHARACTERSKILLS_H
