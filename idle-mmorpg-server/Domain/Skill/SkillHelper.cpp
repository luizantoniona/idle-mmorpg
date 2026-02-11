#include "SkillHelper.h"

namespace Domain {

SkillType SkillHelper::stringToType( const std::string& type ) {
    SkillType enumType = SkillType::UNKNOWN;

    if ( type == "AXE_MASTERY" ) {
        enumType = SkillType::AXE_MASTERY;

    } else if ( type == "DAGGER_MASTERY" ) {
        enumType = SkillType::DAGGER_MASTERY;

    } else if ( type == "SWORD_MASTERY" ) {
        enumType = SkillType::SWORD_MASTERY;

    } else if ( type == "FIST_MASTERY" ) {
        enumType = SkillType::FIST_MASTERY;

    } else if ( type == "SHIELD_MASTERY" ) {
        enumType = SkillType::SHIELD_MASTERY;

    } else if ( type == "INVOCATION" ) {
        enumType = SkillType::INVOCATION;

    } else if ( type == "RESTORATION" ) {
        enumType = SkillType::RESTORATION;

    } else if ( type == "ENDURANCE" ) {
        enumType = SkillType::ENDURANCE;

    } else if ( type == "MEDITATION" ) {
        enumType = SkillType::MEDITATION;

    } else if ( type == "VITALITY" ) {
        enumType = SkillType::VITALITY;

    } else if ( type == "FISHING" ) {
        enumType = SkillType::FISHING;

    } else if ( type == "HERBALISM" ) {
        enumType = SkillType::HERBALISM;

    } else if ( type == "MINING" ) {
        enumType = SkillType::MINING;

    } else if ( type == "WOODCUTTING" ) {
        enumType = SkillType::WOODCUTTING;
    }

    return enumType;
}

std::string SkillHelper::typeToString( SkillType type ) {
    switch ( type ) {
    case SkillType::AXE_MASTERY:
        return "AXE_MASTERY";

    case SkillType::DAGGER_MASTERY:
        return "DAGGER_MASTERY";

    case SkillType::SWORD_MASTERY:
        return "SWORD_MASTERY";

    case SkillType::FIST_MASTERY:
        return "FIST_MASTERY";

    case SkillType::SHIELD_MASTERY:
        return "SHIELD_MASTERY";

    case SkillType::INVOCATION:
        return "INVOCATION";

    case SkillType::RESTORATION:
        return "RESTORATION";

    case SkillType::ENDURANCE:
        return "ENDURANCE";

    case SkillType::MEDITATION:
        return "MEDITATION";

    case SkillType::VITALITY:
        return "VITALITY";

    case SkillType::FISHING:
        return "FISHING";

    case SkillType::HERBALISM:
        return "HERBALISM";

    case SkillType::MINING:
        return "MINING";

    case SkillType::WOODCUTTING:
        return "WOODCUTTING";

    default:
        return "";
    }
}

} // namespace Domain
