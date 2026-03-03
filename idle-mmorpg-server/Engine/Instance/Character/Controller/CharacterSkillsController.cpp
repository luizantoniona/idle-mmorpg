#include "CharacterSkillsController.h"

#include <Domain/Skill/SkillHelper.h>

namespace Engine {

CharacterSkillsController::CharacterSkillsController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                      Domain::Character& character,
                                                      Manager::SkillManager& skillManager ) :
    CharacterController( eventBus, messageSender ),
    _characterSkills( character.skills() ),
    _skillManager( skillManager ) {

    _eventBus.subscribe( CharacterEventType::SKILL_EXPERIENCE_GAINED, [ this ]( const CharacterEvent& event ) {
        onSkillExperienceGained( event );
    } );
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

void CharacterSkillsController::applyExperience( Domain::CharacterSkill* characterSkill, int xpGained ) {
    int newXp = characterSkill->experience() + xpGained;

    int xpNeeded = characterSkill->skill()->experienceForNextLevel( characterSkill->level() );

    while ( newXp >= xpNeeded ) {

        newXp -= xpNeeded;
        characterSkill->setLevel( characterSkill->level() + 1 );

        applyMilestone( characterSkill );

        xpNeeded = characterSkill->skill()->experienceForNextLevel( characterSkill->level() );

        Json::Value payload;
        payload[ "skill" ] = static_cast<int>( characterSkill->type() );
        _eventBus.publish( CharacterEvent( CharacterEventType::SKILL_LEVEL_GAINED, payload ) );
    }

    characterSkill->setExperience( newXp );
}

void CharacterSkillsController::applyMilestone( Domain::CharacterSkill* characterSkill ) {
    const Domain::Skill* skillData = characterSkill->skill();

    if ( !skillData ) {
        return;
    }

    for ( const auto& milestone : skillData->millestones() ) {

        if ( milestone.level() == characterSkill->level() ) {

            for ( const auto& bonus : milestone.bonuses() ) {
                applyMilestoneBonus( bonus );
            }
        }
    }
}

void CharacterSkillsController::applyMilestoneBonus( const Domain::SkillMilestoneBonus& milestoneBonus ) {
    const std::string& type = milestoneBonus.type();
    const std::string& id = milestoneBonus.id();
    double value = milestoneBonus.value();

    if ( type == "vital" ) {

        CharacterEventType eventType;

        if ( id == "health" ) {
            eventType = CharacterEventType::VITAL_MAX_HEALTH_GAINED;

        } else if ( id == "mana" ) {
            eventType = CharacterEventType::VITAL_MAX_MANA_GAINED;

        } else if ( id == "stamina" ) {
            eventType = CharacterEventType::VITAL_MAX_STAMINA_GAINED;

        } else {
            std::cerr << "CharacterSkillsController Unknown id: " << id << std::endl;
            return;
        }

        Json::Value payload;
        payload[ "value" ] = value;
        _eventBus.publish( CharacterEvent( eventType, payload ) );

    } else {
        std::cerr << "CharacterSkillsController Unknown type: " << type << std::endl;
    }
}

void CharacterSkillsController::onSkillExperienceGained( const CharacterEvent& event ) {
    const Json::Value& payload = event.payload();
    if ( !payload.isMember( "skill" ) || !payload.isMember( "experience" ) ) {
        return;
    }

    int xpGained = payload[ "experience" ].asInt();

    if ( xpGained <= 0 ) {
        return;
    }

    Domain::SkillType skillType = static_cast<Domain::SkillType>( payload[ "skill" ].asInt() );

    Domain::CharacterSkill* characterSkill = _characterSkills.skill( skillType );

    if ( !characterSkill ) {

        std::string skillId = Domain::SkillHelper::typeToString( skillType );

        Domain::Skill* skillData = _skillManager.skill( skillId );

        if ( !skillData ) {
            std::cerr << "[CharacterSkillsController] Unknown skill id: " << skillId << std::endl;
            return;
        }

        Domain::CharacterSkill newSkill;
        newSkill.setType( skillType );
        newSkill.setId( skillId );
        newSkill.setLevel( 0 );
        newSkill.setExperience( 0 );
        newSkill.setSkill( skillData );

        _characterSkills.addSkill( newSkill );

        characterSkill = _characterSkills.skill( skillType );
    }

    if ( !characterSkill ) {
        return;
    }

    applyExperience( characterSkill, xpGained );

    _messageSender.sendMessage( MessageSenderType::CHARACTER_SKILLS, _characterSkills.toJson() );
}

} // namespace Engine
