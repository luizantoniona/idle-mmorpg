#include "CharacterProgression.h"

#include <cmath>

namespace Domain {

CharacterProgression::CharacterProgression() :
    _level( 0 ),
    _experience( 0 ),
    _baseExperience( 0.0 ),
    _growthRate( 0.0 ) {
}

Json::Value CharacterProgression::toJson() {
    Json::Value values;
    values[ "level" ] = level();
    values[ "experience" ] = experience();
    values[ "experienceNextLevel" ] = experienceForNextLevel( level() );

    Json::Value progression;
    progression[ "progression" ] = values;
    return progression;
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

int CharacterProgression::experienceForNextLevel( int currentLevel ) const {
    return static_cast<int>( _baseExperience * std::pow( _growthRate, currentLevel ) );
}

double CharacterProgression::baseExperience() const {
    return _baseExperience;
}

void CharacterProgression::setBaseExperience( double baseExperience ) {
    _baseExperience = baseExperience;
}

double CharacterProgression::growthRate() const {
    return _growthRate;
}

void CharacterProgression::setGrowthRate( double growthRate ) {
    _growthRate = growthRate;
}

} // namespace Domain
