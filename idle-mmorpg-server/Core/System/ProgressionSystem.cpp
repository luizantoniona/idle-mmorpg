#include "ProgressionSystem.h"

#include <iostream>

#include <Commons/LevelExperienceHelper.h>
#include <Commons/Singleton.h>
#include <Core/Manager/SkillManager.h>
#include <Core/System/NotificationSystem.h>

namespace Core::System {

ProgressionSystem::ProgressionSystem() {}

void ProgressionSystem::applyExperience( const std::string& sessionId, Model::Character* character, const std::string& skillId, int xpGained ) {
    if ( !character ) {
        return;
    }

    Model::CharacterSkill* characterSkill = character->skills().skill( skillId );

    if ( !characterSkill ) {
        Model::CharacterSkill newSkill;
        newSkill.setId( skillId );
        newSkill.setExperience( 0 );
        newSkill.setLevel( 0 );
        newSkill.setSkill( Commons::Singleton<Core::Manager::SkillManager>::instance().skill( skillId ) );

        if ( !newSkill.skill() ) {
            std::cerr << "ProgressionSystem::applyExperience Unknown skill id: " << skillId << std::endl;
            return;
        }

        character->skills().addSkill( newSkill );
        characterSkill = character->skills().skill( skillId );
    }

    int newXp = characterSkill->experience() + xpGained;
    int xpNeeded = Commons::LevelExperienceHelper::experienceForNextLevel( characterSkill->level() );

    if ( newXp >= xpNeeded ) {
        characterSkill->setLevel( characterSkill->level() + 1 );
        characterSkill->setExperience( newXp - xpNeeded );

        applyMilestone( character, characterSkill );

        NotificationSystem::notifyCharacterAttributes( sessionId, character );
        NotificationSystem::notifyCharacterVitals( sessionId, character );
        NotificationSystem::notifyCharacterProgression( sessionId, character );

    } else {
        characterSkill->setExperience( newXp );
    }

    NotificationSystem::notifyCharacterSkills( sessionId, character );
}

void ProgressionSystem::applyMilestone( Model::Character* character, Model::CharacterSkill* characterSkill ) {
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

void ProgressionSystem::applyMilestoneBonus( Model::Character* character, const Model::SkillMilestoneBonus milestoneBonus ) {
    const std::string& type = milestoneBonus.type();
    const std::string& id = milestoneBonus.id();
    double value = milestoneBonus.value();

    Model::CharacterAttributes& attributes = character->attributes();
    Model::CharacterVitals& vitals = character->vitals();

    if ( type == "attribute" ) {

        if ( id == "strength" ) {
            attributes.setStrength( attributes.strength() + static_cast<int>( value ) );

        } else if ( id == "constitution" ) {
            attributes.setConstitution( attributes.constitution() + static_cast<int>( value ) );

        } else if ( id == "dexterity" ) {
            attributes.setDexterity( attributes.dexterity() + static_cast<int>( value ) );

        } else if ( id == "intelligence" ) {
            attributes.setIntelligence( attributes.intelligence() + static_cast<int>( value ) );

        } else if ( id == "wisdom" ) {
            attributes.setWisdom( attributes.wisdom() + static_cast<int>( value ) );

        } else {
            std::cerr << "[ProgressionSystem] Unknown attribute id: " << id << std::endl;
        }

    } else if ( type == "vital" ) {

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

void ProgressionSystem::applyExperience( const std::string& sessionId, Model::Character* character, int xpGained ) {
    if ( !character ) {
        return;
    }

    auto& progression = character->progression();

    int newXp = progression.experience() + xpGained;
    int xpNeeded = Commons::LevelExperienceHelper::experienceForNextLevel( progression.level() );

    if ( newXp >= xpNeeded ) {
        progression.setLevel( progression.level() + 1 );
        progression.setExperience( newXp - xpNeeded );

        applyLevelUp( character );

        NotificationSystem::notifyCharacterAttributes( sessionId, character );
        NotificationSystem::notifyCharacterVitals( sessionId, character );
        NotificationSystem::notifyCharacterProgression( sessionId, character );

    } else {
        progression.setExperience( newXp );
    }

    NotificationSystem::notifyCharacterSkills( sessionId, character );
}

void ProgressionSystem::applyLevelUp( Model::Character* character ) {
    auto& vitals = character->vitals();
    vitals.setMaxHealth( vitals.maxHealth() + 10 );
    vitals.setMaxMana( vitals.maxMana() + 5 );
    vitals.setMaxStamina( vitals.maxStamina() + 5 );

    auto& attributes = character->attributes();
    int level = character->progression().level();

    if ( level % 10 == 1 || level % 10 == 6 ) {
        attributes.setStrength( attributes.strength() + 1 );
    }

    if ( level % 10 == 2 || level % 10 == 7 ) {
        attributes.setConstitution( attributes.constitution() + 1 );
    }

    if ( level % 10 == 3 || level % 10 == 8 ) {
        attributes.setDexterity( attributes.dexterity() + 1 );
    }

    if ( level % 10 == 4 || level % 10 == 9 ) {
        attributes.setIntelligence( attributes.intelligence() + 1 );
    }

    if ( level % 10 == 5 || level % 10 == 0 ) {
        attributes.setWisdom( attributes.wisdom() + 1 );
    }
}

} // namespace Core::System
