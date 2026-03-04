#ifndef CHARACTERACTIONOPTION_H
#define CHARACTERACTIONOPTION_H

#include <string>
#include <Domain/Skill/SkillType.h>

namespace Domain {

class CharacterActionOption {
public:
    CharacterActionOption();

    int stage() const;
    void setStage(int stage);

    int duration() const;
    void setDuration(int duration);

    int experience() const;
    void setExperience(int experience);

    SkillType skill() const;
    void setSkill(SkillType skill);

    const std::string& itemId() const;
    void setItemId(const std::string& id);

private:
    int _stage;
    int _duration;
    int _experience;
    SkillType _skill;
    std::string _itemId;
};

} // namespace Domain

#endif // CHARACTERACTIONOPTION_H
