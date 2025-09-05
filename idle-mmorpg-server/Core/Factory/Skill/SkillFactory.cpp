#include "SkillFactory.h"

#include <iostream>

#include <Commons/JsonHelper.h>

namespace Core::Factory {

// TODO REVIEW THIS, MAYBE REMOVE FROM JSONS AND MADE SKILLS HARD CODED

std::unordered_map<std::string, std::unique_ptr<Model::Skill> > SkillFactory::createSkills( const std::string& skillsPath ) {
    std::cout << "SkillFactory::createSkills" << std::endl;

    std::unordered_map<std::string, std::unique_ptr<Model::Skill> > skills;

    Json::Value skillsConfig = Commons::JsonHelper::loadJsonFile( skillsPath + "skills.json" );

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

    Json::Value skillJson = Commons::JsonHelper::loadJsonFile( skillPath );

    auto skill = std::make_unique<Model::Skill>();

    skill->setId( skillJson[ "id" ].asString() );
    skill->setName( skillJson[ "name" ].asString() );
    skill->setDescription( skillJson[ "description" ].asString() );
    skill->setType( skillJson[ "type" ].asString() );

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
