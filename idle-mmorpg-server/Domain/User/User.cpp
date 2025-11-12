#include "User.h"

namespace Domain {

User::User() :
    _idUser( 0 ),
    _dsUsername( "" ),
    _dsPassword( "" ) {
}

int User::idUser() const {
    return _idUser;
}

void User::setIdUser( int idUser ) {
    _idUser = idUser;
}

std::string User::dsUsername() const {
    return _dsUsername;
}

void User::setDsUsername( const std::string& dsUsername ) {
    _dsUsername = dsUsername;
}

std::string User::dsPassword() const {
    return _dsPassword;
}

void User::setDsPassword( const std::string& dsPassword ) {
    _dsPassword = dsPassword;
}

} // namespace Domain
