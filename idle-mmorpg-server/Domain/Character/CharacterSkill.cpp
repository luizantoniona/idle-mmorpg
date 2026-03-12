#include "CharacterSkill.h"

#include <Domain/Skill/SkillHelper.h>

namespace Domain {

CharacterSkill::CharacterSkill() :
    _type( SkillType::UNKNOWN ),
    _level( 0 ),
    _bonusLevel( 0 ),
    _experience( 0 ),
    _skill( nullptr ) {}

Json::Value CharacterSkill::toJson() {
    Json::Value values;
    values[ "type" ] = SkillHelper::typeToString( _type );
    values[ "level" ] = _level;
    values[ "bonusLevel" ] = _bonusLevel;
    values[ "experience" ] = _experience;
    values[ "experienceNextLevel" ] = skill()->experienceForNextLevel( level() );
    values[ "skill" ] = skill()->toJson();
    return values;
}

SkillType CharacterSkill::type() const {
    return _type;
}

void CharacterSkill::setType( SkillType type ) {
    _type = type;
}

int CharacterSkill::level() const {
    return _level;
}

void CharacterSkill::setLevel( int level ) {
    _level = level;
}

int CharacterSkill::bonusLevel() const {
    return _bonusLevel;
}

void CharacterSkill::setBonusLevel( int bonusLevel ) {
    _bonusLevel = bonusLevel;
}

void CharacterSkill::modifyBonusLevel( int modifier ) {
    _bonusLevel += modifier;
}

int CharacterSkill::experience() const {
    return _experience;
}

void CharacterSkill::setExperience( int experience ) {
    _experience = experience;
}

void CharacterSkill::clear() {
    _bonusLevel = 0;
}

Skill* CharacterSkill::skill() const {
    return _skill;
}

void CharacterSkill::setSkill( Skill* skill ) {
    _skill = skill;
}

} // namespace Domain
