#include "CharacterSkills.h"

#include <Commons/Singleton.h>
#include <Core/Manager/SkillManager.h>

namespace Model {

CharacterSkills::CharacterSkills() :
    _skills() {}

Json::Value CharacterSkills::toJson() {
    Json::Value root;

    for ( auto& skill : _skills ) {
        root.append( skill.toJson() );
    }

    return root;
}

std::vector<CharacterSkill>& CharacterSkills::skills() {
    return _skills;
}

CharacterSkill* CharacterSkills::skill( SkillType type ) {
    for ( auto& skill : _skills ) {
        if ( skill.type() == type ) {
            return &skill;
        }
    }

    return nullptr;
}

void CharacterSkills::addSkill( CharacterSkill skill ) {
    _skills.push_back( skill );
}

int CharacterSkills::skillLevel( SkillType type ) {
    CharacterSkill* skillToSee = skill( type );
    return skillToSee ? skillToSee->level() + skillToSee->bonusLevel() : 0;
}

void CharacterSkills::clear() {
    for ( auto& skill : _skills ) {
        skill.clear();
    }
}

} // namespace Model
