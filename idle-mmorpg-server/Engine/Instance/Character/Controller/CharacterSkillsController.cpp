#include "CharacterSkillsController.h"

#include <Domain/Skill/SkillHelper.h>

namespace Engine {

CharacterSkillsController::CharacterSkillsController( std::function<void( MessageSenderType, const Json::Value& )> sendMessage,
                                                      Domain::CharacterSkills& skills,
                                                      Manager::SkillManager& skillManager ) :
    CharacterController( sendMessage ),
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

    sendMessage( MessageSenderType::CHARACTER_SKILLS, _skills.toJson() );
}

void CharacterSkillsController::onTickWorld() {
}

void CharacterSkillsController::onExitWorld() {
}

} // namespace Engine
