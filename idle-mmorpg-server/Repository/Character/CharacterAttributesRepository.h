#ifndef CHARACTERATTRIBUTESREPOSITORY_H
#define CHARACTERATTRIBUTESREPOSITORY_H

#include <memory>

#include <Model/Character/CharacterAttributes.h>
#include <Repository/Repository.h>

namespace Repository {

class CharacterAttributesRepository : public Repository {
public:
    explicit CharacterAttributesRepository();

    bool createAttributes( int idCharacter );

    bool updateCharacterAttributes( int idCharacter, const Model::CharacterAttributes& attributes );

    std::unique_ptr<Model::CharacterAttributes> findByCharacterId( int idCharacter );
};

} // namespace Repository

#endif // CHARACTERATTRIBUTESREPOSITORY_H
