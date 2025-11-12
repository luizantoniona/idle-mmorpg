#ifndef TRADESYSTEM_H
#define TRADESYSTEM_H

#include <Domain/Character/Character.h>
#include <Domain/World/Location/Location.h>

namespace Core::System {

class TradeSystem {
public:
    static void characterTradeDenizen( const std::string& sessionId, Domain::Character* character, const Domain::Location* location, const Json::Value& payload );
};

} // namespace Core::System

#endif // TRADESYSTEM_H
