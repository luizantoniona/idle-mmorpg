#ifndef LOCATIONHELPER_H
#define LOCATIONHELPER_H

#include <Model/Character/Character.h>
#include <Model/World/Location/Location.h>

namespace Commons {

class LocationHelper {
public:
    static bool canCharacterPerformAction( Model::Character* character, const Model::LocationAction& action );
    static bool canCharacterUseConnections( Model::Character* character, const Model::LocationConnection& connection );
};

} // namespace Commons

#endif // LOCATIONHELPER_H
