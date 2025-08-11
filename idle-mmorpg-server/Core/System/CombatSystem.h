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

    void computeRegeneration( const std::string& sessionId, Model::Character* character );

    void computeLoot( std::unordered_map<std::string, Model::Character*> characters, std::vector<std::unique_ptr<Model::Creature>> creatures );
    void computeExperience( std::unordered_map<std::string, Model::Character*> characters, std::vector<std::unique_ptr<Model::Creature>> creatures );

private:
    std::string combatSkill( Model::Character* character );

private:
    Model::Location* _location;
    ProgressionSystem _progressionSystem;
};

} // namespace Core::System

#endif // COMBATSYSTEM_H
