#include "ActionOption.h"

namespace Domain {

ActionOption::ActionOption() :
    _stage( 0 ),
    _duration( 0 ),
    _experience( 0 ),
    _skill( SkillType::UNKNOWN ),
    _itemId( "" ) {
}

int ActionOption::stage() const {
    return _stage;
}

void ActionOption::setStage( int stage ) {
    _stage = stage;
}

int ActionOption::duration() const {
    return _duration;
}

void ActionOption::setDuration( int duration ) {
    _duration = duration;
}

int ActionOption::experience() const {
    return _experience;
}

void ActionOption::setExperience( int experience ) {
    _experience = experience;
}

SkillType ActionOption::skill() const {
    return _skill;
}

void ActionOption::setSkill( SkillType skill ) {
    _skill = skill;
}

const std::string& ActionOption::itemId() const {
    return _itemId;
}

void ActionOption::setItemId( const std::string& id ) {
    _itemId = id;
}

} // namespace Domain
