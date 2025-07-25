#ifndef CHARACTERSKILL_H
#define CHARACTERSKILL_H

#include <string>

namespace Model {

class CharacterSkill {
public:
    CharacterSkill();

    std::string id() const;
    void setId( const std::string& id );

    int level() const;
    void setLevel( int level );

    int experience() const;
    void setExperience( int experience );

private:
    std::string _id;
    int _level;
    int _experience;
};

}

#endif // CHARACTERSKILL_H
