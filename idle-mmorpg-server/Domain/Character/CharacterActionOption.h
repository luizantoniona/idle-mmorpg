#ifndef CHARACTERACTIONOPTION_H
#define CHARACTERACTIONOPTION_H

#include <string>

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

    const std::string& itemId() const;
    void setItemId(const std::string& id);

    std::string description() const;
    void setDescription( const std::string& description );

private:
    int _stage;
    int _duration;
    int _experience;
    std::string _itemId;
    std::string _description;
};

} // namespace Domain

#endif // CHARACTERACTIONOPTION_H
