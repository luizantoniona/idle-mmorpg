#include "CharacterSkills.h"

namespace Domain {

CharacterSkills::CharacterSkills() :
    _skills() {}

Json::Value CharacterSkills::toJson() {
    Json::Value values;
    for ( auto& [ type, skill ] : _skills ) {
        values.append( skill.toJson() );
    }

    Json::Value skills;
    skills[ "skills" ] = values;
    return skills;
}

std::unordered_map<SkillType, CharacterSkill>& CharacterSkills::skills() {
    return _skills;
}

CharacterSkill* CharacterSkills::skill( SkillType type ) {
    auto it = _skills.find( type );

    if ( it == _skills.end() ) {
        return nullptr;
    }

    return &it->second;
}

void CharacterSkills::addSkill( const CharacterSkill& skill ) {
    _skills[ skill.type() ] = skill;
}

int CharacterSkills::skillLevel( SkillType type ) const {
    auto it = _skills.find( type );

    if ( it == _skills.end() ) {
        return 0;
    }

    return it->second.level() + it->second.bonusLevel();
}

void CharacterSkills::clear() {
    _skills.clear();
}

} // namespace Domain
