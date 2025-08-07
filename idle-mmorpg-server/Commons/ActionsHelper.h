#ifndef ACTIONSHELPER_H
#define ACTIONSHELPER_H

#include <Model/Character/Character.h>
#include <Model/World/Location/Location.h>

namespace Commons {

class ActionsHelper {
public:
    static bool canCharacterPerformAction( Model::Character* character, const Model::LocationAction& action );
};

} // namespace Commons

#endif // ACTIONSHELPER_H
