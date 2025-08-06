#ifndef CHARACTEREQUIPMENTREPOSITORY_H
#define CHARACTEREQUIPMENTREPOSITORY_H

#include <Model/Character/CharacterEquipment.h>
#include <Repository/Repository.h>

namespace Repository {

class CharacterEquipmentRepository : public Repository {
public:
    explicit CharacterEquipmentRepository();

    bool createEquipment( int idCharacter );
    bool updateEquipment( int idCharacter, const Model::CharacterEquipment& equipment );

    std::unique_ptr<Model::CharacterEquipment> findByCharacterId( int idCharacter );
};

} // namespace Repository

#endif // CHARACTEREQUIPMENTREPOSITORY_H
