#include "NetworkSession.h"

namespace Network {

NetworkSession::NetworkSession() :
    _idUser( 0 ),
    _username( "" ),
    _uuid( "" ),
    _createdAt() {}

int NetworkSession::idUser() const {
    return _idUser;
}

void NetworkSession::setIdUser( const int idUser ) {
    _idUser = idUser;
}

std::string NetworkSession::username() const {
    return _username;
}

void NetworkSession::setUsername( const std::string& username ) {
    _username = username;
}

std::string NetworkSession::uuid() const {
    return _uuid;
}

void NetworkSession::setUuid( const std::string& uuid ) {
    _uuid = uuid;
}

std::chrono::system_clock::time_point NetworkSession::createdAt() const {
    return _createdAt;
}

void NetworkSession::setCreatedAt( std::chrono::system_clock::time_point createdAt ) {
    _createdAt = createdAt;
}

drogon::WebSocketConnectionPtr NetworkSession::connection() const {
    return _wsConnection;
}

void NetworkSession::setConnection( const drogon::WebSocketConnectionPtr& connection ) {
    _wsConnection = connection;
}

bool NetworkSession::hasActiveConnection() const {
    if ( !_wsConnection ) {
        return false;
    }

    return _wsConnection->connected();
}

} // namespace Network
