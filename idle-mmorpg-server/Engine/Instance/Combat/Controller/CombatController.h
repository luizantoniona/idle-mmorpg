#ifndef COMBATCONTROLLER_H
#define COMBATCONTROLLER_H

#include <Domain/Creature/Creature.h>
#include <Engine/Instance/Character/CharacterInstance.h>
#include <Engine/Manager/Server/ServerConfigurationManager.h>

namespace Engine {

class CombatController {
public:
    explicit CombatController( Manager::ServerConfigurationManager& serverManager );
    virtual ~CombatController();

    void resolveCharacterAttack( CharacterInstance& attacker, Domain::Creature& target );
    void resolveCreatureAttack( Domain::Creature& attacker, CharacterInstance& target );

    void computeCharactersLoot( std::unordered_map<std::string, CharacterInstance*> characters, std::vector<Domain::Creature*> creatures );
    void computeCharactersExperience( std::unordered_map<std::string, CharacterInstance*> characters, std::vector<Domain::Creature*> creatures );

private:
    Manager::ServerConfigurationManager& _serverManager;
};

} // namespace Engine

#endif // COMBATCONTROLLER_H
