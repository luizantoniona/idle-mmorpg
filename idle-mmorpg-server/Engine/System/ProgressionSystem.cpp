#include "ProgressionSystem.h"

#include <iostream>

#include <Commons/Singleton.h>
#include <Core/Manager/SkillManager.h>
#include <Core/System/NotificationSystem.h>
#include <Helper/LevelExperienceHelper.h>
#include <Helper/SkillHelper.h>

namespace Core::System {

ProgressionSystem::ProgressionSystem() {
}

void ProgressionSystem::applyExperience( const std::string& sessionId, Domain::Character* character, const Domain::SkillType& skillType, int xpGained ) {
    if ( !character ) {
        return;
    }

    Domain::CharacterSkill* characterSkill = character->skills().skill( skillType );

    if ( !characterSkill ) {

        const std::string skillId = Helper::SkillHelper::enumToString( skillType );

        Domain::CharacterSkill newSkill;
        newSkill.setType( skillType );
        newSkill.setId( skillId );
        newSkill.setExperience( 0 );
        newSkill.setLevel( 0 );
        newSkill.setSkill( Commons::Singleton<Engine::SkillManager>::instance().skill( skillId ) );

        if ( !newSkill.skill() ) {
            std::cerr << "ProgressionSystem::applyExperience Unknown skill id: " << skillId << std::endl;
            return;
        }

        character->skills().addSkill( newSkill );
        characterSkill = character->skills().skill( skillType );
    }

    int newXp = characterSkill->experience() + xpGained;
    int xpNeeded = Helper::LevelExperienceHelper::experienceForNextLevel( characterSkill->level() );

    if ( newXp >= xpNeeded ) {
        characterSkill->setLevel( characterSkill->level() + 1 );
        characterSkill->setExperience( newXp - xpNeeded );

        applyMilestone( character, characterSkill );

        NotificationSystem::notifyCharacterVitals( sessionId, character );

    } else {
        characterSkill->setExperience( newXp );
    }

    NotificationSystem::notifyCharacterSkills( sessionId, character );
}

void ProgressionSystem::applyMilestone( Domain::Character* character, Domain::CharacterSkill* characterSkill ) {
    const auto& skillData = characterSkill->skill();

    if ( !skillData ) {
        return;
    }

    for ( const auto& milestone : skillData->millestones() ) {

        if ( milestone.level() == characterSkill->level() ) {

            for ( const auto& bonus : milestone.bonuses() ) {
                applyMilestoneBonus( character, bonus );
            }
        }
    }
}

void ProgressionSystem::applyMilestoneBonus( Domain::Character* character, const Domain::SkillMilestoneBonus milestoneBonus ) {
    const std::string& type = milestoneBonus.type();
    const std::string& id = milestoneBonus.id();
    double value = milestoneBonus.value();

    Domain::CharacterVitals& vitals = character->vitals();

    if ( type == "vital" ) {

        if ( id == "health" ) {
            vitals.setMaxHealth( vitals.maxHealth() + static_cast<int>( value ) );

        } else if ( id == "mana" ) {
            vitals.setMaxMana( vitals.maxMana() + static_cast<int>( value ) );

        } else if ( id == "stamina" ) {
            vitals.setMaxStamina( vitals.maxStamina() + static_cast<int>( value ) );

        } else {
            std::cerr << "[ProgressionSystem] Unknown vital id: " << id << std::endl;
        }

    } else {
        std::cerr << "[ProgressionSystem] Unknown milestone bonus type: " << type << std::endl;
    }
}

void ProgressionSystem::applyExperience( const std::string& sessionId, Domain::Character* character, int xpGained ) {
    if ( !character ) {
        return;
    }

    auto& progression = character->progression();

    int newXp = progression.experience() + xpGained;
    int xpNeeded = Helper::LevelExperienceHelper::experienceForNextLevel( progression.level() );

    if ( newXp >= xpNeeded ) {
        progression.setLevel( progression.level() + 1 );
        progression.setExperience( newXp - xpNeeded );

        applyLevelUp( character );

        NotificationSystem::notifyCharacterVitals( sessionId, character );

    } else {
        progression.setExperience( newXp );
    }

    NotificationSystem::notifyCharacterProgression( sessionId, character );
}

void ProgressionSystem::applyLevelUp( Domain::Character* character ) {
    auto& vitals = character->vitals();
    vitals.setMaxHealth( vitals.maxHealth() + 10 );
    vitals.setMaxMana( vitals.maxMana() + 5 );
    vitals.setMaxStamina( vitals.maxStamina() + 5 );
}

} // namespace Core::System
