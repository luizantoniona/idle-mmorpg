#include "SkillFactory.h"

#include <iostream>

#include <Helper/JsonHelper.h>
#include <Helper/SkillHelper.h>

namespace Core::Factory {

// TODO REVIEW THIS, MAYBE REMOVE FROM JSONS AND MADE SKILLS HARD CODED

std::unordered_map<std::string, std::unique_ptr<Model::Skill> > SkillFactory::createSkills( const std::string& skillsPath ) {
    std::cout << "SkillFactory::createSkills" << std::endl;

    std::unordered_map<std::string, std::unique_ptr<Model::Skill> > skills;

    Json::Value skillsConfig = Helper::JsonHelper::loadJsonFile( skillsPath + "skills.json" );

    for ( const auto& skillEntry : skillsConfig["skills"] ) {
        std::string skillPath = skillsPath + skillEntry.asString() + ".json";

        auto skill = createSkill( skillPath );
        if ( skill ) {
            skills[skill->id()] = std::move( skill );
        } else {
            std::cerr << "Failed to load skill: " << skillPath << std::endl;
        }
    }

    std::cout << "SkillFactory::createSkills Number of skills loaded: " << skills.size() << std::endl;

    return skills;
}

std::unique_ptr<Model::Skill> SkillFactory::createSkill( const std::string& skillPath ) {
    std::cout << "SkillFactory::createSkill Skill: " << skillPath << std::endl;

    Json::Value skillJson = Helper::JsonHelper::loadJsonFile( skillPath );

    const std::string skillId = skillJson[ "id" ].asString();

    if ( Helper::SkillHelper::stringToEnum( skillId ) == Model::SkillType::UNKNOWN ) {
        std::cerr << "Unmaped skill: " << skillId << std::endl;
        return nullptr;
    }

    auto skill = std::make_unique<Model::Skill>();

    skill->setType( Helper::SkillHelper::stringToEnum( skillId ) );
    skill->setId( skillId );
    skill->setName( skillJson[ "name" ].asString() );
    skill->setDescription( skillJson[ "description" ].asString() );
    skill->setCategory( skillJson[ "category" ].asString() );

    const auto& milestonesJson = skillJson[ "milestones" ];
    for ( const auto& milestoneJson : milestonesJson ) {
        Model::SkillMilestone milestone;
        milestone.setLevel( milestoneJson[ "level" ].asInt() );

        const auto& bonusesJson = milestoneJson[ "bonuses" ];
        for ( const auto& bonusJson : bonusesJson ) {
            Model::SkillMilestoneBonus milestoneBonus;

            milestoneBonus.setType( bonusJson[ "type" ].asString() );
            milestoneBonus.setId( bonusJson[ "id" ].asString() );
            milestoneBonus.setValue( bonusJson[ "value" ].asDouble() );
            milestone.addBonus( milestoneBonus );
        }

        skill->addMilestone( milestone );
    }

    return skill;
}

} // namespace Core::Factory
