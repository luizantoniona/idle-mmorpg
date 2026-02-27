#include "SkillManager.h"

#include <Domain/Skill/SkillHelper.h>

#include "SkillFactory.h"

namespace Manager {

SkillManager::SkillManager() :
    _skills() {}

void SkillManager::initialize( const std::string& skillsPath ) {
    _skills = Manager::SkillFactory::createSkills( skillsPath );
}

Domain::Skill* SkillManager::skill( const std::string& skillId ) {
    auto it = _skills.find( skillId );
    if ( it != _skills.end() ) {
        return it->second.get();
    }

    return nullptr;
}

Domain::Skill* SkillManager::skill( Domain::SkillType skillType ) {
    std::string skillId = Domain::SkillHelper::typeToString( skillType );
    return skill( skillId );
}

} // namespace Manager
