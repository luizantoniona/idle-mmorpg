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

private:
    static bool checkSkillRequirement( Model::Character* character, const Model::Requirement& requirement );
    static bool checkItemRequirement( Model::Character* character, const Model::Requirement& requirement );
    static bool checkEquipmentRequirement( Model::Character* character, const Model::Requirement& requirement );
    static bool checkQuestRequirement( Model::Character* character, const Model::Requirement& requirement );
};

} // namespace Helper

#endif // LOCATIONHELPER_H
