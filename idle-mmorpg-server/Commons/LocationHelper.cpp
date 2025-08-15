#include "LocationHelper.h"

namespace Commons {

bool LocationHelper::canCharacterPerformAction( Model::Character* character, const Model::LocationAction& action ) {
    const std::string& characterStructure = character->coordinates().currentStructure();
    const std::string& actionStructure = action.structure();

    if ( !actionStructure.empty() && characterStructure != actionStructure ) {
        return false;
    }

    if ( actionStructure.empty() && !characterStructure.empty() ) {
        return false;
    }

    for ( const auto& requirement : action.requirements() ) {
        const std::string& type = requirement.type();
        const std::string& id = requirement.id();

        if ( type == "skill" ) {

            Model::CharacterSkill* skill = character->skills().skill( id );
            if ( !skill || skill->level() < requirement.level() ) {
                return false;
            }

        } else if ( type == "item" ) {
            // TODO: Implementar verificação de inventário
            // if ( !character->hasItemInCategory( requirement.category() ) ) {
            return false;
            // }

        } else {
            return false;
        }
    }

    return true;
}

bool LocationHelper::canCharacterUseConnections( Model::Character* character, const Model::LocationConnection& connection ) {
    // TODO: Verify if can use the connection;

    return true;
}

bool LocationHelper::canCharacterInteractDenizen( Model::Character* character, const Model::Denizen& denizen ) {
    const std::string& characterStructure = character->coordinates().currentStructure();
    const std::string& denizenStructure = denizen.structure();

    if ( !denizenStructure.empty() && characterStructure != denizenStructure ) {
        return false;
    }

    if ( denizenStructure.empty() && !characterStructure.empty() ) {
        return false;
    }

    // TODO: Verify conditions in the future;

    return true;
}

bool LocationHelper::canCharacterSeeDenizenQuest( Model::Character* character, const Model::DenizenQuest& quest ) {
    auto& quests = character->quests();
    const std::string& questId = quest.id();

    if ( quests.isQuestFinished( questId ) ) {
        return false;
    }

    if ( quests.isQuestProceeding( questId ) ) {
        if ( quests.isQuestObjectiveCompleted( questId ) ) {
            return true;
        }

        return false;
    }

    return true;
}

} // namespace Commons
