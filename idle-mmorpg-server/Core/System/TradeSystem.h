#ifndef TRADESYSTEM_H
#define TRADESYSTEM_H

#include <Model/Character/Character.h>
#include <Model/World/Location/Location.h>

namespace Core::System {

class TradeSystem {
public:
    static void characterTradeDenizen( const std::string& sessionId, Model::Character* character, const Model::Location* location, const Json::Value& payload );
};

} // namespace Core::System

#endif // TRADESYSTEM_H
