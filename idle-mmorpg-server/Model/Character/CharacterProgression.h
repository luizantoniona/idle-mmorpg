#ifndef CHARACTERPROGRESSION_H
#define CHARACTERPROGRESSION_H

#include <json/json.h>

namespace Model {

class CharacterProgression {
public:
    CharacterProgression();

    Json::Value toJson();

    int level() const;
    void setLevel( int level );

    int experience() const;
    void setExperience( int experience );

    static int experienceForNextLevel( int currentLevel );

private:
    int _level;
    int _experience;
};

} // namespace Model

#endif // CHARACTERPROGRESSION_H
