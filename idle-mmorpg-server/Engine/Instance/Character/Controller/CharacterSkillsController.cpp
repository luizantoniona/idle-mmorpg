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

    _eventBus.subscribe( CharacterEventType::ITEM_EQUIPPED, [ this ]( const CharacterEvent& event ) {
        onItemEquipped( event );
    } );
}

void CharacterSkillsController::onEnterWorld() {
    for ( auto& [type, skill] : _characterSkills.skills() ) {
        Domain::Skill* resolved = _skillManager.skill( type );

        if ( !resolved ) {
            continue;
        }

        skill.setSkill( resolved );
    }

    _messageSender.sendMessage( MessageSenderType::CHARACTER_SKILLS, _characterSkills.toJson() );
}

void CharacterSkillsController::onLeaveWorld() {
}

void CharacterSkillsController::onTick() {
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

        Domain::Skill* skillData = _skillManager.skill( skillType );

        if ( !skillData ) {
            std::cerr << "[CharacterSkillsController] Unknown skill" << std::endl;
            return;
        }

        Domain::CharacterSkill newSkill;
        newSkill.setType( skillType );
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

void CharacterSkillsController::onItemEquipped( const CharacterEvent& event ) {
    // TODO: Apply item bonus on skills in the future
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

    const auto& milestone = skillData->milestone();

    if ( milestone.interval() <= 0 ) {
        return;
    }

    if ( characterSkill->level() % milestone.interval() != 0 ) {
        return;
    }

    double value = milestone.value();

    CharacterEventType eventType;

    switch ( milestone.type() ) {

    case Domain::SkillMilestoneType::VITAL_HEALTH:
        eventType = CharacterEventType::VITAL_MAX_HEALTH_GAINED;
        break;

    case Domain::SkillMilestoneType::VITAL_MANA:
        eventType = CharacterEventType::VITAL_MAX_MANA_GAINED;
        break;

    case Domain::SkillMilestoneType::VITAL_STAMINA:
        eventType = CharacterEventType::VITAL_MAX_STAMINA_GAINED;
        break;

    default:
        std::cerr << "CharacterSkillsController Unknown milestone type" << std::endl;
        return;
    }

    Json::Value payload;
    payload[ "value" ] = value;
    _eventBus.publish( CharacterEvent( eventType, payload ) );
}

} // namespace Engine
