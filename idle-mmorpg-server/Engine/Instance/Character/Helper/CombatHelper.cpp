#include "CombatHelper.h"

namespace Engine {

double CombatHelper::attackSpeedByItem( const Domain::Item* item ) {
    if ( !item ) {
        return 1.0;
    }

    switch ( item->category() ) {
    // --- Weapons ---
    case Domain::ItemCategoryType::AXE:
        return 4.0;

    case Domain::ItemCategoryType::DAGGER:
        return 2.0;

    case Domain::ItemCategoryType::SWORD:
        return 3.0;

    default:
        return 0.0;
    }
}

Domain::SkillType CombatHelper::skillTypeByItem( const Domain::Item* item ) {
    if ( !item ) {
        return Domain::SkillType::FIST_MASTERY;
    }

    switch ( item->category() ) {
    // --- Weapons ---
    case Domain::ItemCategoryType::AXE:
        return Domain::SkillType::AXE_MASTERY;

    case Domain::ItemCategoryType::DAGGER:
        return Domain::SkillType::DAGGER_MASTERY;

    case Domain::ItemCategoryType::SWORD:
        return Domain::SkillType::SWORD_MASTERY;

    // --- OffHand ---
    case Domain::ItemCategoryType::SHIELD:
        return Domain::SkillType::SHIELD_MASTERY;

    default:
        return Domain::SkillType::UNKNOWN;
    }
}

} // namespace Engine
