#include "CharacterSkill.h"

#include <Helper/LevelExperienceHelper.h>

namespace Model {

CharacterSkill::CharacterSkill() :
    _type( SkillType::UNKNOWN ),
    _id( "" ),
    _level( 0 ),
    _bonusLevel( 0 ),
    _experience( 0 ),
    _skill( nullptr ) {
}

Json::Value CharacterSkill::toJson() {
    Json::Value root;
    root[ "id" ] = id();
    root[ "level" ] = level();
    root[ "bonusLevel" ] = bonusLevel();
    root[ "experience" ] = experience();
    root[ "experienceNextLevel" ] = Helper::LevelExperienceHelper::experienceForNextLevel( level() );
    root[ "skill" ] = skill()->toJson();
    return root;
}

SkillType CharacterSkill::type() const {
    return _type;
}

void CharacterSkill::setType( SkillType type ) {
    _type = type;
}

std::string CharacterSkill::id() const {
    return _id;
}

void CharacterSkill::setId( const std::string& id ) {
    _id = id;
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

} // namespace Model
