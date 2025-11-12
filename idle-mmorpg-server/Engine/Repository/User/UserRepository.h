#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <memory>

#include <Domain/User/User.h>
#include <Engine/Repository/Repository.h>

namespace Repository {

class UserRepository : public Repository {
public:
    explicit UserRepository();

    bool createUser( std::string& username, std::string& password );

    std::unique_ptr<Domain::User> findByUsernameAndPassword( const std::string& username, const std::string& password );
};

} // namespace Repository

#endif // USERREPOSITORY_H
