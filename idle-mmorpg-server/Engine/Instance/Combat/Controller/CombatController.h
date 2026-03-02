#ifndef COMBATCONTROLLER_H
#define COMBATCONTROLLER_H

#include <Domain/Creature/Creature.h>
#include <Engine/Instance/Character/CharacterInstance.h>

namespace Engine {

class CombatController {
public:
    explicit CombatController();
    virtual ~CombatController();

    void resolveCharacterAttack( CharacterInstance& attacker, Domain::Creature& target );
    void estimateCharacterAttackSpeed( CharacterInstance& attacker );

    void resolveCreatureAttack( Domain::Creature& attacker, CharacterInstance& target );
    void estimateCreatureAttackSpeed( Domain::Creature& attacker );
};

} // namespace Engine

#endif // COMBATCONTROLLER_H
