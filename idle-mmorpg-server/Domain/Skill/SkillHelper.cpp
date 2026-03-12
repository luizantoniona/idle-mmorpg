#include "SkillHelper.h"

#include <algorithm>
#include <array>
#include <string_view>

namespace Domain {

namespace {
constexpr std::array<std::pair<std::string_view, SkillType>, static_cast<int>( SkillType::UNKNOWN )> SKILL_TYPE_TABLE = { {
    { "AXE_MASTERY", SkillType::AXE_MASTERY },
    { "DAGGER_MASTERY", SkillType::DAGGER_MASTERY },
    { "SWORD_MASTERY", SkillType::SWORD_MASTERY },
    { "FIST_MASTERY", SkillType::FIST_MASTERY },
    { "SHIELD_MASTERY", SkillType::SHIELD_MASTERY },

    { "INVOCATION", SkillType::INVOCATION },
    { "RESTORATION", SkillType::RESTORATION },

    { "ENDURANCE", SkillType::ENDURANCE },
    { "MEDITATION", SkillType::MEDITATION },
    { "VITALITY", SkillType::VITALITY },

    { "FISHING", SkillType::FISHING },
    { "HERBALISM", SkillType::HERBALISM },
    { "MINING", SkillType::MINING },
    { "WOODCUTTING", SkillType::WOODCUTTING },
} };

constexpr std::array<std::pair<std::string_view, SkillMilestoneType>, static_cast<int>( SkillMilestoneType::UNKNOWN )> SKILL_MILESTONE_TYPE_TABLE = { {
    { "VITAL_HEALTH", SkillMilestoneType::VITAL_HEALTH },
    { "VITAL_MANA", SkillMilestoneType::VITAL_MANA },
    { "VITAL_STAMINA", SkillMilestoneType::VITAL_STAMINA },
} };
}

SkillType SkillHelper::stringToType( const std::string& type ) {
    auto it = std::find_if( SKILL_TYPE_TABLE.begin(), SKILL_TYPE_TABLE.end(), [&]( const auto& pair ) {
            return pair.first == type;
        } );

    return it != SKILL_TYPE_TABLE.end() ? it->second : SkillType::UNKNOWN;
}

std::string SkillHelper::typeToString( SkillType type ) {
    auto it = std::find_if( SKILL_TYPE_TABLE.begin(), SKILL_TYPE_TABLE.end(), [&]( const auto& pair ) {
            return pair.second == type;
        } );

    return it != SKILL_TYPE_TABLE.end() ? std::string( it->first ) : "";
}

SkillMilestoneType SkillHelper::stringToMilestoneType( const std::string& type ) {
    auto it = std::find_if( SKILL_MILESTONE_TYPE_TABLE.begin(), SKILL_MILESTONE_TYPE_TABLE.end(), [&]( const auto& pair ) {
            return pair.first == type;
        } );

    return it != SKILL_MILESTONE_TYPE_TABLE.end() ? it->second : SkillMilestoneType::UNKNOWN;
}

std::string SkillHelper::milestoneTypeToString( SkillMilestoneType type ) {
    auto it = std::find_if( SKILL_MILESTONE_TYPE_TABLE.begin(), SKILL_MILESTONE_TYPE_TABLE.end(), [&]( const auto& pair ) {
            return pair.second == type;
        } );

    return it != SKILL_MILESTONE_TYPE_TABLE.end() ? std::string( it->first ) : "";
}

} // namespace Domain
