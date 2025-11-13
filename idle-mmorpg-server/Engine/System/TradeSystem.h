#ifndef TRADESYSTEM_H
#define TRADESYSTEM_H

#include <Domain/Character/Character.h>
#include <Domain/World/Location/Location.h>

namespace Engine {

class TradeSystem {
public:
    static void characterTradeDenizen( const std::string& sessionId, Domain::Character* character, const Domain::Location* location, const Json::Value& payload );
};

} // namespace Engine

#endif // TRADESYSTEM_H
