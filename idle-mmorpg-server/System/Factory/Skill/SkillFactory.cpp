#include "SkillFactory.h"

#include <iostream>

#include <Commons/JsonHelper.h>

namespace System::Factory {

std::unordered_map<std::string, std::unique_ptr<Model::Skill> > SkillFactory::createSkills( const std::string& skillsPath ) {
    std::cout << "SkillFactory::createSkills" << std::endl;

    std::unordered_map<std::string, std::unique_ptr<Model::Skill> > skills;

    Json::Value skillsConfig = Commons::JsonHelper::loadJsonFile( skillsPath + "skills.json" );

    const Json::Value& skillsArray = skillsConfig["skills"];
    for ( const auto& skillEntry : skillsArray ) {
        std::string id = skillEntry["id"].asString();
        std::string fullPath = skillsPath + skillEntry["path"].asString();

        skills[id] = createSkill( fullPath );
    }

    std::cout << "SkillFactory::createSkills Number of skills loaded: " << skills.size() << std::endl;

    return skills;
}

std::unique_ptr<Model::Skill> SkillFactory::createSkill( const std::string& skillPath ) {
    std::cout << "SkillFactory::createSkill Skill: " << skillPath << std::endl;

    Json::Value skillJson = Commons::JsonHelper::loadJsonFile( skillPath );

    auto skill = std::make_unique<Model::Skill>();

    skill->setId( skillJson["id"].asString() );
    skill->setName( skillJson["name"].asString() );
    skill->setDescription( skillJson["description"].asString() );
    skill->setType( skillJson["type"].asString() );

    const auto& milestonesJson = skillJson["milestones"];
    for ( const auto& milestoneJson : milestonesJson ) {
        Model::SkillMilestone milestone;
        milestone.setLevel( milestoneJson["level"].asInt() );

        const auto& bonusesJson = milestoneJson["bonuses"];
        for ( const auto& bonusJson : bonusesJson ) {
            Model::SkillMilestoneAttributeBonus milestoneAttributeBonus;
            milestoneAttributeBonus.setAttribute( bonusJson["attribute"].asString() );
            milestoneAttributeBonus.setValue( bonusJson["value"].asInt() );
            milestone.addBonus( milestoneAttributeBonus );
        }

        skill->addMilestone( milestone );
    }

    return skill;
}

} // namespace System::Factory
