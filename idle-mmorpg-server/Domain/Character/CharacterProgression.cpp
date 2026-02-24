#include "CharacterProgression.h"

#include <Domain/Shared/LevelExperienceHelper.h>

namespace Domain {

CharacterProgression::CharacterProgression() :
    _level( 0 ),
    _experience( 0 ) {}

Json::Value CharacterProgression::toJson() {
    Json::Value values;
    values[ "level" ] = level();
    values[ "experience" ] = experience();
    values[ "experienceNextLevel" ] = Helper::LevelExperienceHelper::experienceForNextLevel( level() );

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

} // namespace Domain
