#include "CharacterProgression.h"

namespace Model {

CharacterProgression::CharacterProgression() :
    _level( 0 ),
    _experience( 0 ) {}

Json::Value CharacterProgression::toJson() {
    Json::Value root;
    root[ "level" ] = level();
    root[ "experience" ] = experience();

    //TODO: Send missing experience to next level;

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

} // namespace Model
