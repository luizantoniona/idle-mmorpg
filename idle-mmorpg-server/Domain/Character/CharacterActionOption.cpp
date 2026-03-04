#include "CharacterActionOption.h"

namespace Domain {

CharacterActionOption::CharacterActionOption() :
    _stage(0),
    _duration(0),
    _experience(0),
    _skill(SkillType::UNKNOWN),
    _itemId("") {
}

int CharacterActionOption::stage() const {
    return _stage;
}

void CharacterActionOption::setStage(int stage) {
    _stage = stage;
}

int CharacterActionOption::duration() const {
    return _duration;
}

void CharacterActionOption::setDuration(int duration) {
    _duration = duration;
}

int CharacterActionOption::experience() const {
    return _experience;
}

void CharacterActionOption::setExperience(int experience) {
    _experience = experience;
}

SkillType CharacterActionOption::skill() const {
    return _skill;
}

void CharacterActionOption::setSkill(SkillType skill) {
    _skill = skill;
}

const std::string& CharacterActionOption::itemId() const {
    return _itemId;
}

void CharacterActionOption::setItemId(const std::string& id) {
    _itemId = id;
}

} // namespace Domain
