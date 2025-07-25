#ifndef CHARACTERSKILLS_H
#define CHARACTERSKILLS_H

#include <string>
#include <unordered_map>

#include "CharacterSkill.h"

namespace Model {

class CharacterSkills {
public:
    CharacterSkills();

    std::unordered_map<std::string, CharacterSkill> skills() const;
    void setSkills( const std::unordered_map<std::string, CharacterSkill>& skills );
    void addSkill( const CharacterSkill& skill );

private:
    std::unordered_map<std::string, CharacterSkill> _skills;
};

} // namespace Model

#endif // CHARACTERSKILLS_H
