#include "SkillManager.h"

#include <Domain/Skill/SkillHelper.h>

#include "SkillFactory.h"

namespace Manager {

SkillManager::SkillManager() :
    _skills() {}

void SkillManager::initialize( const std::string& skillsPath ) {
    _skills = Manager::SkillFactory::createSkills( skillsPath );
}

Domain::Skill* SkillManager::skill( Domain::SkillType skillType ) const {
    auto it = _skills.find( skillType );

    if ( it != _skills.end() ) {
        return it->second.get();
    }

    return nullptr;
}

} // namespace Manager
