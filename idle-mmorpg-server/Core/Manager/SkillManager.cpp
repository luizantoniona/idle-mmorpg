#include "SkillManager.h"

#include <Core/Factory/Skill/SkillFactory.h>
#include <Helper/SkillHelper.h>

namespace Core::Manager {

SkillManager::SkillManager() :
    _skills() {}

void SkillManager::initialize( const std::string& skillsPath ) {
    _skills = Core::Factory::SkillFactory::createSkills( skillsPath );
}

Model::Skill* SkillManager::skill( const std::string& idSkill ) {
    auto it = _skills.find( idSkill );
    if ( it != _skills.end() ) {
        return it->second.get();
    }

    return nullptr;
}

Model::Skill* SkillManager::skill( Model::SkillType typeSkill ) {
    std::string skillId = Helper::SkillHelper::enumToString( typeSkill );
    return skill( skillId );
}

} // namespace Core::Manager
