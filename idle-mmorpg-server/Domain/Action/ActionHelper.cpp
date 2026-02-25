#include "ActionHelper.h"

#include <algorithm>
#include <array>
#include <string_view>

namespace Domain {

namespace {
constexpr std::array<std::pair<std::string_view, ActionType>, static_cast<int>( ActionType::UNKNOWN )> ACTION_TYPE_TABLE = { {
    { "IDLE", ActionType::IDLE },
    { "COMBAT", ActionType::COMBAT },
    { "TRAIN", ActionType::TRAIN },

    { "MINING", ActionType::MINING },
} };
}

ActionType ActionHelper::stringToType( const std::string& type ) {
    auto it = std::find_if( ACTION_TYPE_TABLE.begin(), ACTION_TYPE_TABLE.end(), [&]( const auto& pair ) {
            return pair.first == type;
        } );

    return it != ACTION_TYPE_TABLE.end() ? it->second : ActionType::UNKNOWN;
}

std::string ActionHelper::typeToString( ActionType type ) {
    auto it = std::find_if( ACTION_TYPE_TABLE.begin(), ACTION_TYPE_TABLE.end(), [&]( const auto& pair ) {
            return pair.second == type;
        } );

    return it != ACTION_TYPE_TABLE.end() ? std::string( it->first ) : "";
}

} // namespace Domain
