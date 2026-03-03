#include "CombatController.h"

#include <algorithm>

namespace Engine {

CombatController::CombatController( Manager::ServerConfigurationManager& serverManager ) :
    _serverManager( serverManager ) {
}

CombatController::~CombatController() = default;

void CombatController::resolveCharacterAttack( CharacterInstance& attacker, Domain::Creature& target ) {
    auto& combat = attacker.character().combat();

    if ( combat.attackCounter() < combat.attackDuration() ) {
        combat.setAttackCounter( combat.attackCounter() + 1 );
        return;
    }

    if ( attacker.character().vitals().health() <= 0 ) {
        return;
    }

    if ( target.vitals().health() <= 0 ) {
        return;
    }

    double damage = combat.attack();

    double newHealth = (std::max)( 0.0, target.vitals().health() - damage );
    target.vitals().setHealth( newHealth );

    combat.setAttackCounter( 0 );
}

void CombatController::resolveCreatureAttack( Domain::Creature& attacker, CharacterInstance& target ) {
    auto& combat = attacker.combat();

    if ( combat.attackCounter() < combat.attackDuration() ) {
        combat.setAttackCounter( combat.attackCounter() + 1 );
        return;
    }

    if ( attacker.vitals().health() <= 0 ) {
        return;
    }

    if ( target.character().vitals().health() <= 0 ) {
        return;
    }

    double damage = combat.attack();

    double newHealth = (std::max)( 0.0, target.character().vitals().health() - damage );

    target.character().vitals().setHealth( newHealth );

    combat.setAttackCounter( 0 );
}

void CombatController::computeCharactersLoot( std::unordered_map<std::string, CharacterInstance*> characters, std::vector<Domain::Creature*> creatures ) {
}

void CombatController::computeCharactersExperience( std::unordered_map<std::string, CharacterInstance*> characters, std::vector<Domain::Creature*> creatures ) {
}

} // namespace Engine
