#ifndef CHARACTERINVENTORYREPOSITORY_H
#define CHARACTERINVENTORYREPOSITORY_H

#include <memory>

#include <Model/Character/CharacterInventory.h>
#include <Repository/Repository.h>

namespace Repository {

class CharacterInventoryRepository : public Repository {
public:
    explicit CharacterInventoryRepository();

    bool createInventory( int idCharacter );
    //    bool updateInventory( int idCharacter, const Model::CharacterInventoryModel& inventory );

    //    std::unique_ptr<Model::CharacterInventoryModel> findByCharacterId( int idCharacter );
};

} // namespace Repository

#endif // CHARACTERINVENTORYREPOSITORY_H
