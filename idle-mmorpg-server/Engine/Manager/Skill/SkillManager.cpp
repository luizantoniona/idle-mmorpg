#include "SkillManager.h"

#include <Shared/Helper/SkillHelper.h>

#include "SkillFactory.h"

namespace Engine {

SkillManager::SkillManager() :
    _skills() {}

void SkillManager::initialize( const std::string& skillsPath ) {
    _skills = Engine::SkillFactory::createSkills( skillsPath );
}

Domain::Skill* SkillManager::skill( const std::string& idSkill ) {
    auto it = _skills.find( idSkill );
    if ( it != _skills.end() ) {
        return it->second.get();
    }

    return nullptr;
}

Domain::Skill* SkillManager::skill( Domain::SkillType typeSkill ) {
    std::string skillId = Helper::SkillHelper::enumToString( typeSkill );
    return skill( skillId );
}

} // namespace Engine
