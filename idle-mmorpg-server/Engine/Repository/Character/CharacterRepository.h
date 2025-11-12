#ifndef CHARACTERREPOSITORY_H
#define CHARACTERREPOSITORY_H

#include <memory>
#include <vector>

#include <Domain/Character/Character.h>
#include <Repository/Repository.h>

namespace Repository {

class CharacterRepository : public Repository {
public:
    explicit CharacterRepository();

    int createCharacter( const int idUser, const std::string& dsName );
    bool updateCharacter( Domain::Character character );
    bool deleteCharacter( int idCharacter );

    std::vector<std::unique_ptr<Domain::Character>> findAllByIdUser( const int idUser );

    std::unique_ptr<Domain::Character> findByIdUserAndIdCharacter( const int idUser, const int idCharacter );
};

} // namespace Repository

#endif // CHARACTERREPOSITORY_H
