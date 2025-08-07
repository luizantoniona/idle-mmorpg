#include "ProgressionSystem.h"

#include <iostream>

#include <Commons/LevelExperienceHelper.h>
#include <Commons/Singleton.h>
#include <Core/Manager/SkillManager.h>

namespace Core::System {

ProgressionSystem::ProgressionSystem() :
    _notificationSystem() {}

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
        character->skills().addSkill( newSkill );
        characterSkill = character->skills().skill( skillId );
    }

    int newXp = characterSkill->experience() + xpGained;
    int xpNeeded = Commons::LevelExperienceHelper::experienceForNextLevel( characterSkill->level() );

    if ( newXp >= xpNeeded ) {
        characterSkill->setLevel( characterSkill->level() + 1 );
        characterSkill->setExperience( newXp - xpNeeded );

        applyMilestone( character, characterSkill );

        _notificationSystem.notifyCharacterAttributes( sessionId, character );
        _notificationSystem.notifyCharacterVitals( sessionId, character );
        _notificationSystem.notifyCharacterProgression( sessionId, character );

    } else {
        characterSkill->setExperience( newXp );
    }

    _notificationSystem.notifyCharacterSkills( sessionId, character );
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

    if ( type == "attribute" ) {

        if ( id == "strength" ) {
            character->attributes().setBaseStrength( character->attributes().baseStrength() + static_cast<int>( value ) );

        } else if ( id == "constitution" ) {
            character->attributes().setBaseConstitution( character->attributes().baseConstitution() + static_cast<int>( value ) );

        } else if ( id == "dexterity" ) {
            character->attributes().setBaseDexterity( character->attributes().baseDexterity() + static_cast<int>( value ) );

        } else if ( id == "intelligence" ) {
            character->attributes().setBaseIntelligence( character->attributes().baseIntelligence() + static_cast<int>( value ) );

        } else if ( id == "wisdom" ) {
            character->attributes().setBaseWisdom( character->attributes().baseWisdom() + static_cast<int>( value ) );

        } else if ( id == "charisma" ) {
            character->attributes().setBaseCharisma( character->attributes().baseCharisma() + static_cast<int>( value ) );

        } else {
            std::cerr << "[ProgressionSystem] Unknown attribute id: " << id << std::endl;
        }

    } else if ( type == "vital" ) {

        if ( id == "health" ) {
            character->vitals().setMaxHealth( character->vitals().maxHealth() + static_cast<int>( value ) );

        } else if ( id == "health_regen" ) {
            character->vitals().setBaseHealthRegen( character->vitals().baseHealthRegen() + static_cast<double>( value ) );

        } else if ( id == "mana" ) {
            character->vitals().setMaxMana( character->vitals().maxMana() + static_cast<int>( value ) );

        } else if ( id == "mana_regen" ) {
            character->vitals().setBaseManaRegen( character->vitals().baseManaRegen() + static_cast<double>( value ) );

        } else if ( id == "stamina" ) {
            character->vitals().setMaxStamina( character->vitals().maxStamina() + static_cast<int>( value ) );

        } else if ( id == "stamina_regen" ) {
            character->vitals().setBaseStaminaRegen( character->vitals().baseStaminaRegen() + static_cast<double>( value ) );

        } else {
            std::cerr << "[ProgressionSystem] Unknown vital id: " << id << std::endl;
        }

    } else {
        std::cerr << "[ProgressionSystem] Unknown milestone bonus type: " << type << std::endl;
    }
}

} // namespace Core::System
