#include "CombatController.h"

#include <algorithm>
#include <cmath>

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

    Json::Value payload;
    payload[ "value" ] = -1.0;
    attacker.publishEvent( CharacterEventType::VITAL_STAMINA_CHANGED, payload );

    // TODO: Should apply experience on endurance skill.

    double damage = combat.attack();

    // TODO: Should apply experience on attack weapon skill.

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

    // TODO: Should apply experience on vitallity skill.

    Json::Value payload;
    payload[ "value" ] = -damage;
    target.publishEvent( CharacterEventType::VITAL_HEALTH_CHANGED, payload );

    combat.setAttackCounter( 0 );
}

void CombatController::computeCharactersLoot( std::unordered_map<std::string, CharacterInstance*>& characters, std::vector<Domain::Creature*>& creatures ) {
    if ( characters.empty() ) {
        return;
    }

    std::vector<std::string> sessionIds;
    sessionIds.reserve( characters.size() );

    for ( const auto& [ sessionId, _ ] : characters ) {
        sessionIds.push_back( sessionId );
    }

    for ( const auto& creature : creatures ) {

        for ( const auto& lootEntry : creature->loot() ) {

            double roll = static_cast<double>( rand() ) / RAND_MAX;

            if ( roll > lootEntry.chance() ) {
                continue;
            }

            const std::string& randomSession = sessionIds[ rand() % sessionIds.size() ];

            CharacterInstance* receiverInstance = characters.at( randomSession );

            auto& receiver = receiverInstance->character();

            int amount = lootEntry.minAmount() + ( rand() % ( lootEntry.maxAmount() - lootEntry.minAmount() + 1 ) );

            if ( amount <= 0 ) {
                continue;
            }

            const std::string itemId = lootEntry.id();

            Json::Value payload;
            payload[ "item" ] = itemId;
            payload[ "amount" ] = amount;

            receiverInstance->publishEvent( CharacterEventType::ITEM_GAINED, payload );
        }
    }
}

void CombatController::computeCharactersExperience( std::unordered_map<std::string, CharacterInstance*>& characters, std::vector<Domain::Creature*>& creatures ) {
    if ( characters.empty() ) {
        return;
    }

    double totalXP = 0.0;
    for ( const auto& creature : creatures ) {
        totalXP += creature->experience();
    }

    if ( totalXP <= 0.0 ) {
        return;
    }

    int xpPerCharacter = static_cast<int>( std::ceil( totalXP / characters.size() ) );

    for ( const auto& [ sessionId, characterInstance ] : characters ) {
        Json::Value payload;
        payload[ "value" ] = xpPerCharacter;
        characterInstance->publishEvent( CharacterEventType::PROGRESSION_EXPERIENCE_GAINED, payload );
    }
}

} // namespace Engine
