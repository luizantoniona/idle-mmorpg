#include "NetworkServer.h"

#include <drogon/drogon.h>

namespace Network {

NetworkServer::NetworkServer() :
    _sessions( {} ) {}

NetworkServer::~NetworkServer() {
    clearSessions();
}

std::string NetworkServer::createSession( const int idUser, const std::string& username ) {
    std::lock_guard lock( _sessionMutex );

    std::string sessionId = drogon::utils::getUuid();

    Network::NetworkSession session;
    session.setIdUser( idUser );
    session.setUsername( username );
    session.setUuid( sessionId );
    session.setCreatedAt( std::chrono::system_clock::now() );

    _sessions[ sessionId ] = session;

    return sessionId;
}

bool NetworkServer::deleteSession( const std::string& uuid ) {
    std::lock_guard lock( _sessionMutex );

    return _sessions.erase( uuid ) > 0;
}

bool NetworkServer::clearSessions() {
    std::lock_guard lock( _sessionMutex );

    _sessions.clear();
    return true;
}

std::optional<Network::NetworkSession> NetworkServer::getSession( const std::string& uuid ) const {
    std::lock_guard lock( _sessionMutex );

    auto it = _sessions.find( uuid );
    if ( it != _sessions.end() ) {
        return it->second;
    }

    return std::nullopt;
}

void NetworkServer::bindConnectionToSession( const std::string& uuid, const drogon::WebSocketConnectionPtr& wsConnection ) {
    std::lock_guard<std::mutex> lock( _sessionMutex );

    auto it = _sessions.find( uuid );
    if ( it != _sessions.end() ) {
        it->second.setConnection( wsConnection );
    }
}

void NetworkServer::unbindConnectionFromSession( const std::string& uuid ) {
    std::lock_guard<std::mutex> lock( _sessionMutex );

    auto it = _sessions.find( uuid );
    if ( it != _sessions.end() ) {
        it->second.setConnection( nullptr );
    }
}

bool NetworkServer::isSessionConnected( const std::string& uuid ) {
    std::lock_guard lock( _sessionMutex );

    auto it = _sessions.find( uuid );
    if ( it == _sessions.end() ) {
        return false;
    }

    return it->second.hasActiveConnection();

}

} // namespace Network
