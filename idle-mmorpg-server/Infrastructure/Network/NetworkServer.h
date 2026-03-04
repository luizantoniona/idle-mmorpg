#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>

#include "NetworkSession.h"

namespace Network {

class NetworkServer {
public:
    NetworkServer();
    ~NetworkServer();

    std::string createSession( const int idUser, const std::string& username );

    bool deleteSession( const std::string& uuid );

    bool clearSessions();

    std::optional<NetworkSession> getSession( const std::string& uuid ) const;

private:
    mutable std::mutex _sessionMutex;
    std::unordered_map<std::string, Network::NetworkSession> _sessions;
};

} // namespace Network

#endif // NETWORKSERVER_H
