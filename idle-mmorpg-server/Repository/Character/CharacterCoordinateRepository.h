#ifndef CHARACTERCOORDINATEREPOSITORY_H
#define CHARACTERCOORDINATEREPOSITORY_H

#include <memory>

#include <Model/Character/CharacterCoordinates.h>
#include <Repository/Repository.h>

namespace Repository {

class CharacterCoordinateRepository : public Repository {
public:
    explicit CharacterCoordinateRepository();

    bool createCoordinates( int idCharacter );
    bool updateCoordinates( int idCharacter, const Model::CharacterCoordinates& coordinates );

    std::unique_ptr<Model::CharacterCoordinates> findByCharacterId( int idCharacter );
};

} // namespace Repository

#endif // CHARACTERCOORDINATEREPOSITORY_H
