#ifndef CHARACTERCOMBATATTRIBUTESREPOSITORY_H
#define CHARACTERCOMBATATTRIBUTESREPOSITORY_H

#include <memory>

#include <Model/Character/CharacterCombatAttributes.h>
#include <Repository/Repository.h>

namespace Repository {

class CharacterCombatAttributesRepository : public Repository {
public:
    explicit CharacterCombatAttributesRepository();

    bool createAttributes( int idCharacter );
    bool updateAttributes( int idCharacter, const Model::CharacterCombatAttributes& attributes );

    std::unique_ptr<Model::CharacterCombatAttributes> findByCharacterId( int idCharacter );
};

} // namespace Repository

#endif // CHARACTERCOMBATATTRIBUTESREPOSITORY_H
