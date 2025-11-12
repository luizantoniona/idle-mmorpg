#ifndef CHARACTERCOORDINATEREPOSITORY_H
#define CHARACTERCOORDINATEREPOSITORY_H

#include <memory>

#include <Domain/Character/CharacterCoordinates.h>
#include <Repository/Repository.h>

namespace Repository {

class CharacterCoordinateRepository : public Repository {
public:
    explicit CharacterCoordinateRepository();

    bool createCoordinates( int idCharacter );
    bool updateCoordinates( int idCharacter, const Domain::CharacterCoordinates& coordinates );

    std::unique_ptr<Domain::CharacterCoordinates> findByCharacterId( int idCharacter );
};

} // namespace Repository

#endif // CHARACTERCOORDINATEREPOSITORY_H
