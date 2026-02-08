#ifndef CHARACTEREQUIPMENTREPOSITORY_H
#define CHARACTEREQUIPMENTREPOSITORY_H

#include <Domain/Character/CharacterEquipment.h>
#include <Repository/Repository.h>

namespace Repository {

class CharacterEquipmentRepository : public Repository {
public:
    explicit CharacterEquipmentRepository();

    bool createEquipment( int idCharacter );
    bool updateEquipment( int idCharacter, Domain::CharacterEquipment& equipment );

    std::unique_ptr<Domain::CharacterEquipment> findByCharacterId( int idCharacter );
};

} // namespace Repository

#endif // CHARACTEREQUIPMENTREPOSITORY_H
