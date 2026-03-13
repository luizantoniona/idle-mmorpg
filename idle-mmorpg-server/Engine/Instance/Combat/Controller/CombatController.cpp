#include "CombatController.h"

#include <algorithm>
#include <cmath>

#include <Engine/Instance/Character/Helper/CombatHelper.h>

namespace Engine {

CombatController::CombatController( Manager::ServerConfigurationManager& serverManager ) :
    _serverManager( serverManager ) {
}

CombatController::~CombatController() = default;

void CombatController::resolveCharacterAttack( CharacterInstance& attacker, Domain::Creature& target ) {
    auto& attackerCombat = attacker.character().combat();

    if ( attackerCombat.attackCounter() < attackerCombat.attackDuration() ) {
        attackerCombat.setAttackCounter( attackerCombat.attackCounter() + 1 );
        return;
    }

    if ( attacker.character().vitals().health() <= 0 ) {
        return;
    }

    if ( target.vitals().health() <= 0 ) {
        return;
    }

    Json::Value staminaPayload;
    staminaPayload[ "value" ] = -1.0;
    attacker.publishEvent( CharacterEventType::VITAL_STAMINA_CHANGED, staminaPayload );

    double attack = attackerCombat.attack();
    double defense = target.combat().defense();

    double damage = ( attack * attack ) / (std::max)( 1.0, attack + defense );

    double targetHealth = target.vitals().health();
    double effectiveDamage = (std::min)( damage, targetHealth );

    double newHealth = (std::max)( 0.0, targetHealth - damage );
    target.vitals().setHealth( newHealth );

    attackerCombat.setAttackCounter( 0 );

    const Domain::Item* weapon = attacker.character().equipment().weapon().item();
    Domain::SkillType skill = CombatHelper::skillTypeByItem( weapon );
    if ( skill != Domain::SkillType::UNKNOWN ) {
        Json::Value xpPayload;
        xpPayload[ "skill" ] = static_cast<int>( skill );
        xpPayload[ "experience" ] = (std::max)( 1.0, effectiveDamage );
        attacker.publishEvent( CharacterEventType::SKILL_EXPERIENCE_GAINED, xpPayload );
    }
}

void CombatController::resolveCreatureAttack( Domain::Creature& attacker, CharacterInstance& target ) {
    auto& attackerCombat = attacker.combat();

    if ( attackerCombat.attackCounter() < attackerCombat.attackDuration() ) {
        attackerCombat.setAttackCounter( attackerCombat.attackCounter() + 1 );
        return;
    }

    if ( attacker.vitals().health() <= 0 ) {
        return;
    }

    if ( target.character().vitals().health() <= 0 ) {
        return;
    }

    double attack = attackerCombat.attack();
    double defense = target.character().combat().defense();

    double damage = ( attack * attack ) / (std::max)( 1.0, attack + defense );

    attackerCombat.setAttackCounter( 0 );

    const Domain::Item* offhand = target.character().equipment().offhand().item();
    if ( offhand && offhand->category() == Domain::ItemCategoryType::SHIELD ) {

        int blockLevel = target.character().skills().skillLevel( Domain::SkillType::SHIELD_MASTERY );

        double blockChance = blockLevel / ( blockLevel + attack );
        blockChance = (std::min)( 0.75, blockChance );

        double roll = static_cast<double>( rand() ) / RAND_MAX;

        if ( roll < blockChance ) {
            double targetHealth = target.character().vitals().health();
            double effectiveDamage = (std::min)( damage, targetHealth );

            Json::Value xpPayload;
            xpPayload[ "skill" ] = static_cast<int>( Domain::SkillType::SHIELD_MASTERY );
            xpPayload[ "experience" ] = (std::max)( 1.0, effectiveDamage );
            target.publishEvent( CharacterEventType::SKILL_EXPERIENCE_GAINED, xpPayload );

            return;
        }

        Json::Value xpPayload;
        xpPayload[ "skill" ] = static_cast<int>( Domain::SkillType::SHIELD_MASTERY );
        xpPayload[ "experience" ] = ( 1.0 );
        target.publishEvent( CharacterEventType::SKILL_EXPERIENCE_GAINED, xpPayload );
    }

    Json::Value payload;
    payload[ "value" ] = -damage;
    target.publishEvent( CharacterEventType::VITAL_HEALTH_CHANGED, payload );
}

void CombatController::computeCharactersLoot( std::unordered_map<std::string, CharacterInstance*>& characters, std::vector<Domain::Creature*>& creatures ) {
    if ( characters.empty() ) {
        return;
    }

    for ( const auto& creature : creatures ) {

        for ( const auto& [ sessionId, receiverInstance ] : characters ) {

            for ( const auto& lootEntry : creature->loot() ) {

                double roll = static_cast<double>( rand() ) / RAND_MAX;

                if ( roll > lootEntry.chance() ) {
                    continue;
                }

                int amount = lootEntry.minAmount() + ( rand() % ( lootEntry.maxAmount() - lootEntry.minAmount() + 1 ) );

                if ( amount <= 0 ) {
                    continue;
                }

                const std::string& itemId = lootEntry.id();

                Json::Value payload;
                payload[ "item" ] = itemId;
                payload[ "amount" ] = amount;
                receiverInstance->publishEvent( CharacterEventType::ITEM_GAINED, payload );
            }
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
