#include "ActionsHelper.h"

namespace Commons {

bool ActionsHelper::canCharacterPerformAction( Model::Character* character, const Model::LocationAction& action ) {
    if ( !character ) {
        return false;
    }

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

} // namespace Commons
