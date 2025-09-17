#ifndef LOCATIONHELPER_H
#define LOCATIONHELPER_H

#include <Model/Character/Character.h>
#include <Model/World/Location/Location.h>

namespace Helper {

class LocationHelper {
public:
    static bool canCharacterPerformAction( Model::Character* character, const Model::LocationAction& action );
    static bool canCharacterUseConnections( Model::Character* character, const Model::LocationConnection& connection );
    static bool canCharacterInteractDenizen( Model::Character* character, const Model::Denizen& denizen );
    static bool canCharacterSeeDenizenQuest( Model::Character* character, const Model::DenizenQuest& quest );
};

} // namespace Helper

#endif // LOCATIONHELPER_H
