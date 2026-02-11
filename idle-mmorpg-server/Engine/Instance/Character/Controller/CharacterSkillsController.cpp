#include "CharacterSkillsController.h"

#include <Domain/Skill/SkillHelper.h>

namespace Engine {

CharacterSkillsController::CharacterSkillsController( Domain::CharacterSkills& skills, Manager::SkillManager& skillManager ) :
    _skills( skills ),
    _skillManager( skillManager ) {
}

void CharacterSkillsController::onEnterWorld() {
    for ( auto& skill : _skills.skills() ) {
        Domain::Skill* resolved = _skillManager.skill( skill.id() );
        if ( !resolved ) {
            continue;
        }

        skill.setSkill( resolved );
        skill.setType( Domain::SkillHelper::stringToType( skill.id() ) );
    }
}

void CharacterSkillsController::onExitWorld() {
}

} // namespace Engine
