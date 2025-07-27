#include "ActionSystem.h"

#include <Commons/Singleton.h>
#include <Core/Manager/SkillManager.h>

namespace Core::System {

ActionSystem::ActionSystem() {
}

bool Core::System::ActionSystem::canPerformAction( Model::Character* character, const Model::LocationAction& action ) {
    if ( !character ) {
        return false;
    }

    for ( const auto& requirement : action.requirements() ) {
        const std::string& type = requirement.type();
        const std::string& id = requirement.id();

        if ( type == "skill" ) {
            Model::CharacterSkill* skill = character->skills().skill( id );

            if ( !skill ) {
                auto characterSkill = std::make_unique<Model::CharacterSkill>();
                characterSkill->setId( id );
                characterSkill->setExperience( 0 );
                characterSkill->setLevel( 0 );
                characterSkill->setSkill( Commons::Singleton<Core::Manager::SkillManager>::instance().skill( id ) );

                character->skills().addSkill( std::move( characterSkill ) );

                skill = character->skills().skill( id );
            }

            if ( !skill || skill->level() < requirement.level() ) {
                return false;
            }

        } else if ( type == "item" ) {
            // TODO: Implementar verificação de inventário
            // if ( !character->hasItemInCategory( requirement.category() ) ) {
            return false;
            // }

        } else {
            // Tipo de requisito desconhecido
            return false;
        }
    }

    return true;
}

void ActionSystem::startAction( Model::Character* character, const Model::LocationAction& action ) {
}

} // namespace Core::System
