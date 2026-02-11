#ifndef CHARACTEREQUIPMENTCONTROLLER_H
#define CHARACTEREQUIPMENTCONTROLLER_H

#include <Domain/Character/CharacterEquipment.h>
#include <Manager/Item/ItemManager.h>

namespace Engine {

class CharacterEquipmentController {
public:
    explicit CharacterEquipmentController( Domain::CharacterEquipment& equipment, Manager::ItemManager& itemManager );

    void onEnterWorld();
    void onExitWorld();

private:
    Domain::CharacterEquipment& _equipment;
    Manager::ItemManager& _itemManager;
};

} // namespace Engine

#endif // CHARACTEREQUIPMENTCONTROLLER_H
