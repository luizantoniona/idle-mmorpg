#ifndef CHARACTERPROGRESSION_H
#define CHARACTERPROGRESSION_H

#include <json/json.h>

namespace Domain {

class CharacterProgression {
public:
    CharacterProgression();

    Json::Value toJson();

    int level() const;
    void setLevel( int level );

    int experience() const;
    void setExperience( int experience );

    int experienceForNextLevel( int currentLevel ) const;

    double baseExperience() const;
    void setBaseExperience( double baseExperience );

    double growthRate() const;
    void setGrowthRate( double growthRate );

private:
    int _level;
    int _experience;

    double _baseExperience;
    double _growthRate;
};

} // namespace Domain

#endif // CHARACTERPROGRESSION_H
