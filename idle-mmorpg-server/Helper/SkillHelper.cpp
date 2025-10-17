#include "SkillHelper.h"

namespace Helper {

Model::SkillType SkillHelper::stringToEnum( const std::string& type ) {
    Model::SkillType enumType = Model::SkillType::UNKNOWN;

    if ( type == "AXE_MASTERY" ) {
        enumType = Model::SkillType::AXE_MASTERY;

    } else if ( type == "DAGGER_MASTERY" ) {
        enumType = Model::SkillType::DAGGER_MASTERY;

    } else if ( type == "SWORD_MASTERY" ) {
        enumType = Model::SkillType::SWORD_MASTERY;

    } else if ( type == "FIST_MASTERY" ) {
        enumType = Model::SkillType::FIST_MASTERY;

    } else if ( type == "SHIELD_MASTERY" ) {
        enumType = Model::SkillType::SHIELD_MASTERY;

    } else if ( type == "INVOCATION" ) {
        enumType = Model::SkillType::INVOCATION;

    } else if ( type == "RESTORATION" ) {
        enumType = Model::SkillType::RESTORATION;

    } else if ( type == "ENDURANCE" ) {
        enumType = Model::SkillType::ENDURANCE;

    } else if ( type == "MEDITATION" ) {
        enumType = Model::SkillType::MEDITATION;

    } else if ( type == "VITALITY" ) {
        enumType = Model::SkillType::VITALITY;

    } else if ( type == "FISHING" ) {
        enumType = Model::SkillType::FISHING;

    } else if ( type == "HERBALISM" ) {
        enumType = Model::SkillType::HERBALISM;

    } else if ( type == "MINING" ) {
        enumType = Model::SkillType::MINING;

    } else if ( type == "WOODCUTTING" ) {
        enumType = Model::SkillType::WOODCUTTING;
    }

    return enumType;
}

std::string SkillHelper::enumToString( Model::SkillType type ) {
    switch ( type ) {
    case Model::SkillType::AXE_MASTERY:
        return "AXE_MASTERY";

    case Model::SkillType::DAGGER_MASTERY:
        return "DAGGER_MASTERY";

    case Model::SkillType::SWORD_MASTERY:
        return "SWORD_MASTERY";

    case Model::SkillType::FIST_MASTERY:
        return "FIST_MASTERY";

    case Model::SkillType::SHIELD_MASTERY:
        return "SHIELD_MASTERY";

    case Model::SkillType::INVOCATION:
        return "INVOCATION";

    case Model::SkillType::RESTORATION:
        return "RESTORATION";

    case Model::SkillType::ENDURANCE:
        return "ENDURANCE";

    case Model::SkillType::MEDITATION:
        return "MEDITATION";

    case Model::SkillType::VITALITY:
        return "VITALITY";

    case Model::SkillType::FISHING:
        return "FISHING";

    case Model::SkillType::HERBALISM:
        return "HERBALISM";

    case Model::SkillType::MINING:
        return "MINING";

    case Model::SkillType::WOODCUTTING:
        return "WOODCUTTING";

    default:
        return "";
    }
}

} // namespace Helper
