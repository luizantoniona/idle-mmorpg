#include "CharacterSkills.h"

#include <Commons/Singleton.h>
#include <Core/Manager/SkillManager.h>

namespace Model {

CharacterSkills::CharacterSkills() :
    _skills() {}

std::vector<CharacterSkill>& CharacterSkills::skills() {
    return _skills;
}

CharacterSkill* CharacterSkills::skill( const std::string& idSkill ) {
    for ( auto& skill : _skills ) {
        if ( skill.id() == idSkill ) {
            return &skill;
        }
    }

    return nullptr;
}

void CharacterSkills::addSkill( CharacterSkill skill ) {
    _skills.push_back( skill );
}

} // namespace Model
