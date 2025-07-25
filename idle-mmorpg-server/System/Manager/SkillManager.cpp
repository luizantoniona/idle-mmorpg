#include "SkillManager.h"

#include <System/Factory/Skill/SkillFactory.h>

namespace System::Manager {

SkillManager::SkillManager() :
    _skills() {}

void SkillManager::initialize( const std::string& skillsPath ) {
    _skills = System::Factory::SkillFactory::createSkills( skillsPath );
}

} // namespace System::Manager
