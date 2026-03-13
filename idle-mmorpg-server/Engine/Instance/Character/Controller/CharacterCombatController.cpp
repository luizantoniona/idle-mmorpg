#include "CharacterCombatController.h"

#include <Engine/Instance/Character/Helper/CombatHelper.h>

namespace Engine {

CharacterCombatController::CharacterCombatController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                      Domain::Character& character,
                                                      Manager::ServerConfigurationManager& configurationManager ) :
    CharacterController( eventBus, messageSender ),
    _character( character ),
    _characterCombat( character.combat() ),
    _configurationManager( configurationManager ) {

    _eventBus.subscribe( CharacterEventType::ITEM_EQUIPPED, [ this ]( const CharacterEvent& event ) {
        onItemEquipped( event );
    } );

    _eventBus.subscribe( CharacterEventType::SKILL_LEVEL_GAINED, [ this ]( const CharacterEvent& event ) {
        onSkillLeveledUp( event );
    } );
}

void CharacterCombatController::onEnterWorld() {
    recomputeCombatAttributes();
}

void CharacterCombatController::onLeaveWorld() {
}

void CharacterCombatController::onTick() {
}

void CharacterCombatController::handleMessage( MessageReceiverType type, const Json::Value& payload ) {
}

void CharacterCombatController::recomputeCombatAttributes() {
    auto& equipment = _character.equipment();
    auto& skills = _character.skills();

    _characterCombat.clearAttributes();

    const Domain::Item* weaponItem = equipment.weapon().item();
    const Domain::Item* offhandItem = equipment.offhand().item();

    std::vector<const Domain::Item*> items = {
        equipment.helmet().item(),
        equipment.armor().item(),
        equipment.leg().item(),
        equipment.boot().item(),
        weaponItem,
        offhandItem,
        equipment.amulet().item(),
        equipment.ring().item(),
    };

    double attack = 1.0;
    double defense = 0.0;

    for ( const Domain::Item* item : items ) {
        if ( !item ) {
            continue;
        }

        attack += item->combat().attack();
        defense += item->combat().defense();
    }

    Domain::SkillType weaponSkill = CombatHelper::skillTypeByItem( weaponItem );
    if ( auto* skill = skills.skill( weaponSkill ) ) {
        attack += skill->level() * 0.5;
    }

    double speed = CombatHelper::attackSpeedByItem( weaponItem );

    _characterCombat.setAttack( attack );
    _characterCombat.setDefense( defense );
    _characterCombat.setAttackDuration( speed * _configurationManager.tickRate() );
}

void CharacterCombatController::onItemEquipped( const CharacterEvent& event ) {
    recomputeCombatAttributes();
}

void CharacterCombatController::onSkillLeveledUp( const CharacterEvent& event ) {
    recomputeCombatAttributes();
}

} // namespace Engine
