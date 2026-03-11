#include "CharacterCombatController.h"

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

    double attack = 0.0;
    double defense = 0.0;

    for ( const Domain::Item* item : items ) {
        if ( !item ) {
            continue;
        }

        attack += item->combat().attack();
        defense += item->combat().defense();
    }

    auto getSkillForWeapon = []( const Domain::Item* item ) -> Domain::SkillType {
        if ( !item ) {
            return Domain::SkillType::FIST_MASTERY;
        }

        switch ( item->category() ) {

        case Domain::ItemCategory::AXE:
            return Domain::SkillType::AXE_MASTERY;

        case Domain::ItemCategory::DAGGER:
            return Domain::SkillType::DAGGER_MASTERY;

        case Domain::ItemCategory::SWORD:
            return Domain::SkillType::SWORD_MASTERY;

        default:
            return Domain::SkillType::FIST_MASTERY;
        }
    };

    Domain::SkillType weaponSkill = getSkillForWeapon( weaponItem );

    if ( auto* skill = skills.skill( weaponSkill ) ) {
        attack += skill->level() * 0.5;
    }

    double attackSpeed = 0.0;

    if ( weaponItem ) {
        attackSpeed = weaponItem->combat().attackSpeed();

    } else {
        attackSpeed = 0.5;
    }

    _characterCombat.setAttack( attack );
    _characterCombat.setDefense( defense );

    int attackDuration = attackSpeed * _configurationManager.tickRate();
    _characterCombat.setAttackDuration( attackDuration );
}

void CharacterCombatController::onItemEquipped( const CharacterEvent& event ) {
    recomputeCombatAttributes();
}

void CharacterCombatController::onSkillLeveledUp( const CharacterEvent& event ) {
    recomputeCombatAttributes();
}

} // namespace Engine
