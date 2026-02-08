#ifndef CHARACTERINVENTORYREPOSITORY_H
#define CHARACTERINVENTORYREPOSITORY_H

#include <memory>

#include <Domain/Character/CharacterInventory.h>
#include <Repository/Repository.h>

namespace Repository {

class CharacterInventoryRepository : public Repository {
public:
    explicit CharacterInventoryRepository();

    bool createInventory( int idCharacter );
    bool updateInventory( int idCharacter, Domain::CharacterInventory& inventory );

    std::unique_ptr<Domain::CharacterInventory> findByCharacterId( int idCharacter );
};

} // namespace Repository

#endif // CHARACTERINVENTORYREPOSITORY_H
