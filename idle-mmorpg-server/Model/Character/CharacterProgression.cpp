#include "CharacterProgression.h"

namespace Model {

CharacterProgression::CharacterProgression() :
    _level( 0 ),
    _experience( 0 ) {
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
