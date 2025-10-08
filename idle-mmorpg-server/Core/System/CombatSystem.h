#ifndef COMBATSYSTEM_H
#define COMBATSYSTEM_H

#include <unordered_map>

#include <Model/Character/Character.h>
#include <Model/Creature/Creature.h>
#include <Model/World/Location/Location.h>

#include "ProgressionSystem.h"

namespace Core::System {

class CombatSystem {
public:
    explicit CombatSystem( Model::Location* location );

    void computeCombatActionDuration( Model::Character* character );
    void computeCombatActionDuration( Model::Creature* creature );

    void computeHitDamage( const std::string& sessionId, Model::Character* character, Model::Creature* creature );
    void computeHitDamage( Model::Creature* creature, const std::string& sessionId, Model::Character* character );
    void computeSpellDamage( const std::string& sessionId, Model::Character* character, Model::Creature* creature, Model::CharacterSpell* characterSpell );

    void computeLoot( std::unordered_map<std::string, Model::Character*> characters, std::vector<Model::Creature*> creatures );
    void computeExperience( std::unordered_map<std::string, Model::Character*> characters, std::vector<Model::Creature*> creatures );

private:
    bool rollChance( double probability );
    double rollRange( double min, double max );

    std::string combatSkill( Model::Character* character );
    std::string combatSkillByWeapon( const Model::Item* weapon );

private:
    int _tickRate;
    Model::Location* _location;
    ProgressionSystem _progressionSystem;
};

} // namespace Core::System

#endif // COMBATSYSTEM_H
