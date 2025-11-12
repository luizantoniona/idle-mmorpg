#include "SkillHelper.h"

namespace Helper {

Domain::SkillType SkillHelper::stringToEnum( const std::string& type ) {
    Domain::SkillType enumType = Domain::SkillType::UNKNOWN;

    if ( type == "AXE_MASTERY" ) {
        enumType = Domain::SkillType::AXE_MASTERY;

    } else if ( type == "DAGGER_MASTERY" ) {
        enumType = Domain::SkillType::DAGGER_MASTERY;

    } else if ( type == "SWORD_MASTERY" ) {
        enumType = Domain::SkillType::SWORD_MASTERY;

    } else if ( type == "FIST_MASTERY" ) {
        enumType = Domain::SkillType::FIST_MASTERY;

    } else if ( type == "SHIELD_MASTERY" ) {
        enumType = Domain::SkillType::SHIELD_MASTERY;

    } else if ( type == "INVOCATION" ) {
        enumType = Domain::SkillType::INVOCATION;

    } else if ( type == "RESTORATION" ) {
        enumType = Domain::SkillType::RESTORATION;

    } else if ( type == "ENDURANCE" ) {
        enumType = Domain::SkillType::ENDURANCE;

    } else if ( type == "MEDITATION" ) {
        enumType = Domain::SkillType::MEDITATION;

    } else if ( type == "VITALITY" ) {
        enumType = Domain::SkillType::VITALITY;

    } else if ( type == "FISHING" ) {
        enumType = Domain::SkillType::FISHING;

    } else if ( type == "HERBALISM" ) {
        enumType = Domain::SkillType::HERBALISM;

    } else if ( type == "MINING" ) {
        enumType = Domain::SkillType::MINING;

    } else if ( type == "WOODCUTTING" ) {
        enumType = Domain::SkillType::WOODCUTTING;
    }

    return enumType;
}

std::string SkillHelper::enumToString( Domain::SkillType type ) {
    switch ( type ) {
    case Domain::SkillType::AXE_MASTERY:
        return "AXE_MASTERY";

    case Domain::SkillType::DAGGER_MASTERY:
        return "DAGGER_MASTERY";

    case Domain::SkillType::SWORD_MASTERY:
        return "SWORD_MASTERY";

    case Domain::SkillType::FIST_MASTERY:
        return "FIST_MASTERY";

    case Domain::SkillType::SHIELD_MASTERY:
        return "SHIELD_MASTERY";

    case Domain::SkillType::INVOCATION:
        return "INVOCATION";

    case Domain::SkillType::RESTORATION:
        return "RESTORATION";

    case Domain::SkillType::ENDURANCE:
        return "ENDURANCE";

    case Domain::SkillType::MEDITATION:
        return "MEDITATION";

    case Domain::SkillType::VITALITY:
        return "VITALITY";

    case Domain::SkillType::FISHING:
        return "FISHING";

    case Domain::SkillType::HERBALISM:
        return "HERBALISM";

    case Domain::SkillType::MINING:
        return "MINING";

    case Domain::SkillType::WOODCUTTING:
        return "WOODCUTTING";

    default:
        return "";
    }
}

} // namespace Helper
