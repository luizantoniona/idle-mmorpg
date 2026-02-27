#include "CharacterSkillsController.h"

#include <Domain/Skill/SkillHelper.h>

namespace Engine {

CharacterSkillsController::CharacterSkillsController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                      Domain::Character& character,
                                                      Manager::SkillManager& skillManager ) :
    CharacterController( eventBus, messageSender ),
    _characterSkills( character.skills() ),
    _skillManager( skillManager ) {
}

void CharacterSkillsController::onEnterWorld() {
    for ( auto& skill : _characterSkills.skills() ) {
        Domain::Skill* resolved = _skillManager.skill( skill.id() );
        if ( !resolved ) {
            continue;
        }

        skill.setSkill( resolved );
        skill.setType( Domain::SkillHelper::stringToType( skill.id() ) );
    }

    _messageSender.sendMessage( MessageSenderType::CHARACTER_SKILLS, _characterSkills.toJson() );
}

void CharacterSkillsController::onLeaveWorld() {
}

void CharacterSkillsController::onTick() {
}

} // namespace Engine
