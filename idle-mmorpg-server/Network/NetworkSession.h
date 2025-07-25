#ifndef NETWORKSESSION_H
#define NETWORKSESSION_H

#include <chrono>
#include <string>

#include <drogon/WebSocketConnection.h>

namespace Network {

class NetworkSession {
public:
    NetworkSession();

    int idUser() const;
    void setIdUser( const int idUser );

    std::string username() const;
    void setUsername( const std::string& username );

    std::string uuid() const;
    void setUuid( const std::string& uuid );

    std::chrono::system_clock::time_point createdAt() const;
    void setCreatedAt( std::chrono::system_clock::time_point createdAt );

    drogon::WebSocketConnectionPtr connection() const;
    void setConnection( const drogon::WebSocketConnectionPtr& connection );

    bool hasActiveConnection() const;

private:
    int _idUser;
    std::string _username;
    std::string _uuid;
    std::chrono::system_clock::time_point _createdAt;
    drogon::WebSocketConnectionPtr _wsConnection;
};

} // namespace Network

#endif // NETWORKSESSION_H
