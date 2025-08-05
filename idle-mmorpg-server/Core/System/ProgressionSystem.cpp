#include "ProgressionSystem.h"

#include <Commons/LevelExperienceHelper.h>
#include <Commons/Singleton.h>
#include <Core/Manager/SkillManager.h>

namespace Core::System {

ProgressionSystem::ProgressionSystem() :
    _sender() {}

void ProgressionSystem::notifyCharacterProgression( const std::string& sessionId, Model::Character* character ) {
    if ( !character ) {
        return;
    }
    Json::Value payload;
    payload[ "progression" ] = character->progression().toJson();
    _sender.send( sessionId, Message::MessageSenderType::CHARACTER_UPDATE_PROGRESSION, payload );
}

void ProgressionSystem::notifyCharacterSkills( const std::string& sessionId, Model::Character* character ) {
    if ( !character ) {
        return;
    }

    Json::Value payload;
    payload[ "skills" ] = character->skills().toJson();
    _sender.send( sessionId, Message::MessageSenderType::CHARACTER_UPDATE_SKILLS, payload );
}

void ProgressionSystem::applyExperience( const std::string& sessionId, Model::Character* character, const std::string& skillId, int xpGained ) {
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
    int xpNeeded = Commons::LevelExperienceHelper::experienceForNextLevel( skill->level() );

    if ( newXp >= xpNeeded ) {
        skill->setLevel( skill->level() + 1 );
        skill->setExperience( newXp - xpNeeded );

        // TODO APPLY MILESTONES IN THE FUTURE;

    } else {
        skill->setExperience( newXp );
    }

    notifyCharacterSkills( sessionId, character );
}

} // namespace Core::System
