#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <memory>

#include <Model/User/User.h>
#include <Repository/Repository.h>

namespace Repository {

class UserRepository : public Repository {
public:
    explicit UserRepository();

    bool createUser( std::string& username, std::string& password );

    std::unique_ptr<Model::User> findByUsernameAndPassword( const std::string& username, const std::string& password );
};

} // namespace Repository

#endif // USERREPOSITORY_H
