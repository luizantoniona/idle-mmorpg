#include "SkillFactory.h"

#include <iostream>

#include <Domain/Skill/SkillHelper.h>
#include <Shared/Helper/JsonHelper.h>

namespace Manager {

std::unordered_map<Domain::SkillType, std::unique_ptr<Domain::Skill> > SkillFactory::createSkills( const std::string& skillsPath ) {
    std::cout << "SkillFactory::createSkills" << std::endl;

    std::unordered_map<Domain::SkillType, std::unique_ptr<Domain::Skill> > skills;

    Json::Value skillsConfig = Helper::JsonHelper::loadJsonFile( skillsPath + "skills.json" );

    for ( const auto& skillEntry : skillsConfig["skills"] ) {
        std::string skillPath = skillsPath + skillEntry.asString() + ".json";

        auto skill = createSkill( skillPath );
        if ( skill ) {
            skills[skill->type()] = std::move( skill );

        } else {
            std::cerr << "Failed to load skill: " << skillPath << std::endl;
        }
    }

    std::cout << "SkillFactory::createSkills Number of skills loaded: " << skills.size() << std::endl;

    return skills;
}

std::unique_ptr<Domain::Skill> SkillFactory::createSkill( const std::string& skillPath ) {
    std::cout << "SkillFactory::createSkill Skill: " << skillPath << std::endl;

    Json::Value skillJson = Helper::JsonHelper::loadJsonFile( skillPath );

    const std::string skillId = skillJson[ "id" ].asString();

    Domain::SkillType skillType = Domain::SkillHelper::stringToType( skillId );

    if ( skillType == Domain::SkillType::UNKNOWN ) {
        std::cerr << "Unmapped skill: " << skillId << std::endl;
        return nullptr;
    }

    auto skill = std::make_unique<Domain::Skill>();

    skill->setType( skillType );
    skill->setCategory( skillJson[ "category" ].asString() );
    skill->setName( skillJson[ "name" ].asString() );
    skill->setDescription( skillJson[ "description" ].asString() );

    // --- Experience ---
    const auto& expJson = skillJson[ "experience" ];
    skill->setBaseExperience( expJson[ "base" ].asDouble() );
    skill->setGrowthRate( expJson[ "growth" ].asDouble() );

    // --- Milestone ---
    const auto& milestoneJson = skillJson[ "milestone" ];
    if ( !milestoneJson.isNull() ) {
        Domain::SkillMilestone milestone;
        milestone.setInterval( milestoneJson[ "interval" ].asInt() );
        milestone.setType( Domain::SkillHelper::stringToMilestoneType( milestoneJson[ "type" ].asString() ) );
        milestone.setValue( milestoneJson[ "value" ].asDouble() );

        skill->setMilestone( milestone );
    }

    return skill;
}

} // namespace Manager
