#include "LevelExperienceHelper.h"

#include <cmath>

namespace Helper {

int LevelExperienceHelper::experienceForNextLevel( int currentLevel ) {
    const double baseXp = 100.0;
    const double growthRate = 1.05;
    return baseXp * std::pow( growthRate, currentLevel );
}

} // namespace Helper
