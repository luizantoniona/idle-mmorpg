#include "CombatController.h"

namespace Engine {

CombatController::CombatController() {
}

CombatController::~CombatController() = default;

void CombatController::resolveCharacterAttack( CharacterInstance& attacker, Domain::Creature& target ) {
}

void CombatController::estimateCharacterAttackSpeed( CharacterInstance& attacker ) {
}

void CombatController::resolveCreatureAttack( Domain::Creature& attacker, CharacterInstance& target ) {
}

void CombatController::estimateCreatureAttackSpeed( Domain::Creature& attacker ) {
}

} // namespace Engine
