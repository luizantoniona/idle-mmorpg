#ifndef NETWORKSESSION_H
#define NETWORKSESSION_H

#include <chrono>
#include <string>

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

private:
    int _idUser;
    std::string _username;
    std::string _uuid;
    std::chrono::system_clock::time_point _createdAt;
};

} // namespace Network

#endif // NETWORKSESSION_H
