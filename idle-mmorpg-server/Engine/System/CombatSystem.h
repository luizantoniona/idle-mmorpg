#ifndef COMBATSYSTEM_H
#define COMBATSYSTEM_H

#include <unordered_map>

#include <Domain/Character/Character.h>
#include <Domain/Creature/Creature.h>
#include <Domain/World/Location/Location.h>

#include "ProgressionSystem.h"

namespace Core::System {

class CombatSystem {
public:
    explicit CombatSystem( Domain::Location* location );

    void computeCombatActionDuration( Domain::Character* character );
    void computeCombatActionDuration( Domain::Creature* creature );

    void computeHitDamage( const std::string& sessionId, Domain::Character* character, Domain::Creature* creature );
    void computeHitDamage( Domain::Creature* creature, const std::string& sessionId, Domain::Character* character );
    void computeSpellDamage( const std::string& sessionId, Domain::Character* character, Domain::Creature* creature, Domain::CharacterSpell* characterSpell );

    void computeLoot( std::unordered_map<std::string, Domain::Character*> characters, std::vector<Domain::Creature*> creatures );
    void computeExperience( std::unordered_map<std::string, Domain::Character*> characters, std::vector<Domain::Creature*> creatures );

private:
    bool rollChance( double probability );
    double rollRange( double min, double max );

    Domain::SkillType combatSkill( Domain::Character* character );
    Domain::SkillType combatSkillByWeapon( const Domain::Item* weapon );

private:
    int _tickRate;
    Domain::Location* _location;
    ProgressionSystem _progressionSystem;
};

} // namespace Core::System

#endif // COMBATSYSTEM_H
