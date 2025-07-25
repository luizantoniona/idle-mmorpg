#ifndef USER_H
#define USER_H

#include <string>

namespace Model {

class User {
public:
    User();

    int idUser() const;
    void setIdUser( int idUser );

    std::string dsUsername() const;
    void setDsUsername( const std::string& dsUsername );

    std::string dsPassword() const;
    void setDsPassword( const std::string& dsPassword );

private:
    int _idUser;
    std::string _dsUsername;
    std::string _dsPassword;
};

} // namespace Model

#endif // USER_H
