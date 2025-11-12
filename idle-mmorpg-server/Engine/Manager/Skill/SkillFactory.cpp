#include "SkillFactory.h"

#include <iostream>

#include <Domain/Skill/SkillHelper.h>
#include <Shared/Helper/JsonHelper.h>

namespace Engine {

// TODO REVIEW THIS, MAYBE REMOVE FROM JSONS AND MADE SKILLS HARD CODED

std::unordered_map<std::string, std::unique_ptr<Domain::Skill> > SkillFactory::createSkills( const std::string& skillsPath ) {
    std::cout << "SkillFactory::createSkills" << std::endl;

    std::unordered_map<std::string, std::unique_ptr<Domain::Skill> > skills;

    Json::Value skillsConfig = Helper::JsonHelper::loadJsonFile( skillsPath + "skills.json" );

    for ( const auto& skillEntry : skillsConfig[ "skills" ] ) {
        std::string skillPath = skillsPath + skillEntry.asString() + ".json";

        auto skill = createSkill( skillPath );
        if ( skill ) {
            skills[ skill->id() ] = std::move( skill );
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

    if ( Helper::SkillHelper::stringToEnum( skillId ) == Domain::SkillType::UNKNOWN ) {
        std::cerr << "Unmaped skill: " << skillId << std::endl;
        return nullptr;
    }

    auto skill = std::make_unique<Domain::Skill>();

    skill->setType( Helper::SkillHelper::stringToEnum( skillId ) );
    skill->setId( skillId );
    skill->setName( skillJson[ "name" ].asString() );
    skill->setDescription( skillJson[ "description" ].asString() );
    skill->setCategory( skillJson[ "category" ].asString() );

    const auto& milestonesJson = skillJson[ "milestones" ];
    for ( const auto& milestoneJson : milestonesJson ) {
        Domain::SkillMilestone milestone;
        milestone.setLevel( milestoneJson[ "level" ].asInt() );

        const auto& bonusesJson = milestoneJson[ "bonuses" ];
        for ( const auto& bonusJson : bonusesJson ) {
            Domain::SkillMilestoneBonus milestoneBonus;

            milestoneBonus.setType( bonusJson[ "type" ].asString() );
            milestoneBonus.setId( bonusJson[ "id" ].asString() );
            milestoneBonus.setValue( bonusJson[ "value" ].asDouble() );
            milestone.addBonus( milestoneBonus );
        }

        skill->addMilestone( milestone );
    }

    return skill;
}

} // namespace Engine
