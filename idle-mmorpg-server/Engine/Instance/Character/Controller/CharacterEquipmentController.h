#ifndef CHARACTEREQUIPMENTCONTROLLER_H
#define CHARACTEREQUIPMENTCONTROLLER_H

#include <Domain/Character/Character.h>
#include <Engine/Manager/Item/ItemManager.h>

#include "CharacterController.h"

namespace Engine {

class CharacterEquipmentController : public CharacterController {
public:
    explicit CharacterEquipmentController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                           Domain::Character& character,
                                           Manager::ItemManager& itemManager );

    void onEnterWorld() override;
    void onLeaveWorld() override;

    void onTick() override;

private:
    Domain::CharacterEquipment& _characterEquipment;
    Manager::ItemManager& _itemManager;
};

} // namespace Engine

#endif // CHARACTEREQUIPMENTCONTROLLER_H
