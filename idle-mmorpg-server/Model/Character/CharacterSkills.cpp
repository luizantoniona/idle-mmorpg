#include "CharacterSkills.h"

namespace Model {

CharacterSkills::CharacterSkills() :
    _skills() {}

std::unordered_map<std::string, CharacterSkill> CharacterSkills::skills() const {
    return _skills;
}

void CharacterSkills::setSkills( const std::unordered_map<std::string, CharacterSkill>& skills ) {
    _skills = skills;
}

void CharacterSkills::addSkill( const CharacterSkill& skill ) {
    _skills[skill.id()] = skill;
}

} // namespace Model
