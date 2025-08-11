#include "CombatSystem.h"

namespace Core::System {

CombatSystem::CombatSystem( Model::Location* location ) :
    _location( location ),
    _progressionSystem() {}

void CombatSystem::process( const std::string& sessionId, Model::Character* character ) {}

} // namespace Core::System
