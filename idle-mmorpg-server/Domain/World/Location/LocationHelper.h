#ifndef LOCATIONHELPER_H
#define LOCATIONHELPER_H

#include <Domain/Character/Character.h>
#include <Domain/World/Location/Location.h>

namespace Helper {

class LocationHelper {
public:
    static bool canCharacterPerformAction( Domain::Character* character, const Domain::LocationAction& action );
    static bool canCharacterUseConnections( Domain::Character* character, const Domain::LocationConnection& connection );
    static bool canCharacterInteractDenizen( Domain::Character* character, const Domain::Denizen& denizen );
    static bool canCharacterSeeDenizenQuest( Domain::Character* character, const Domain::DenizenQuest& quest );

private:
    static bool checkRequirement( Domain::Character* character, const Domain::Requirement& requirement );
    static bool checkSkillRequirement( Domain::Character* character, const Domain::Requirement& requirement );
    static bool checkItemRequirement( Domain::Character* character, const Domain::Requirement& requirement );
    static bool checkEquipmentRequirement( Domain::Character* character, const Domain::Requirement& requirement );
    static bool checkQuestRequirement( Domain::Character* character, const Domain::Requirement& requirement );
};

} // namespace Helper

#endif // LOCATIONHELPER_H
