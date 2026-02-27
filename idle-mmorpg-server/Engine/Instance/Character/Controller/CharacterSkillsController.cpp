#include "CharacterSkillsController.h"

#include <Domain/Skill/SkillHelper.h>

namespace Engine {

CharacterSkillsController::CharacterSkillsController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                      Domain::CharacterSkills& skills,
                                                      Manager::SkillManager& skillManager ) :
    CharacterController( eventBus, messageSender ),
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

    _messageSender.sendMessage( MessageSenderType::CHARACTER_SKILLS, _skills.toJson() );
}

void CharacterSkillsController::onLeaveWorld() {
}

void CharacterSkillsController::onTick() {
}

} // namespace Engine
