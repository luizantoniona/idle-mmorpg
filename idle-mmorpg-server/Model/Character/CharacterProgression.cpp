#include "CharacterProgression.h"

#include <cmath>

namespace Model {

CharacterProgression::CharacterProgression() :
    _level( 0 ),
    _experience( 0 ) {}

Json::Value CharacterProgression::toJson() {
    Json::Value root;
    root[ "level" ] = level();
    root[ "experience" ] = experience();
    root[ "experienceNextLevel" ] = experienceForNextLevel( level() );

    return root;
}

int CharacterProgression::level() const {
    return _level;
}

void CharacterProgression::setLevel( int level ) {
    _level = level;
}

int CharacterProgression::experience() const {
    return _experience;
}

void CharacterProgression::setExperience( int experience ) {
    _experience = experience;
}

int CharacterProgression::experienceForNextLevel( int currentLevel ) {
    const double baseXp = 100.0;
    const double growthRate = 1.05;
    return baseXp * std::pow( growthRate, currentLevel );
}

} // namespace Model
