#include "SkillProgressionSystem.h"

#include <Commons/Singleton.h>
#include <Core/Manager/SkillManager.h>

namespace Core::System {

SkillProgressionSystem::SkillProgressionSystem() :
    _sender() {
}

void SkillProgressionSystem::notifyCharacterSkills( const std::string& sessionId, Model::Character* character ) {
    if ( !character ) {
        return;
    }

    Json::Value payload;
    payload[ "skills" ] = Json::arrayValue;

    for ( const auto& skill : character->skills().skills() ) {
        Json::Value skillJson;
        skillJson[ "id" ] = skill.id();
        skillJson[ "level" ] = skill.level();
        skillJson[ "experience" ] = skill.experience();
        skillJson[ "experienceNextLevel" ] = experienceForNextLevel( skill.level() );

        payload[ "skills" ].append( skillJson );
    }

    _sender.send( sessionId, Message::MessageSenderType::CHARACTER_UPDATE_SKILLS, payload );
}

void SkillProgressionSystem::applyExperience( const std::string& sessionId, Model::Character* character, const std::string& skillId, int xpGained ) {
    if ( !character ) {
        return;
    }

    Model::CharacterSkill* skill = character->skills().skill( skillId );

    if ( !skill ) {
        Model::CharacterSkill newSkill;
        newSkill.setId( skillId );
        newSkill.setExperience( 0 );
        newSkill.setLevel( 0 );
        newSkill.setSkill( Commons::Singleton<Core::Manager::SkillManager>::instance().skill( skillId ) );
        character->skills().addSkill( newSkill );
        skill = character->skills().skill( skillId );
    }

    int newXp = skill->experience() + xpGained;
    int xpNeeded = experienceForNextLevel( skill->level() );

    if ( newXp >= xpNeeded ) {
        skill->setLevel( skill->level() + 1 );
        skill->setExperience( newXp - xpNeeded );

        // TODO APPLY MILESTONES IN THE FUTURE;

    } else {
        skill->setExperience( newXp );
    }

    notifyCharacterSkills( sessionId, character );
}

int SkillProgressionSystem::experienceForNextLevel( int currentLevel ) const {
    const double baseXp = 100.0;
    const double growthRate = 1.05;
    return baseXp * std::pow( growthRate, currentLevel );
}

} // namespace Core::System
