#include "CharacterSkill.h"

#include <Commons/LevelExperienceHelper.h>

namespace Model {

CharacterSkill::CharacterSkill() :
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
    root[ "experienceNextLevel" ] = Commons::LevelExperienceHelper::experienceForNextLevel( level() );
    root[ "skill" ] = skill()->toJson();
    return root;
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

int CharacterSkill::experience() const {
    return _experience;
}

void CharacterSkill::setExperience( int experience ) {
    _experience = experience;
}

Skill* CharacterSkill::skill() const {
    return _skill;
}

void CharacterSkill::setSkill( Skill* skill ) {
    _skill = skill;
}

} // namespace Model
