#ifndef CHARACTEREQUIPMENTCONTROLLER_H
#define CHARACTEREQUIPMENTCONTROLLER_H

#include <Domain/Character/CharacterEquipment.h>
#include <Engine/Manager/Item/ItemManager.h>

#include "CharacterController.h"

namespace Engine {

class CharacterEquipmentController : public CharacterController {
public:
    explicit CharacterEquipmentController( std::function<void( MessageSenderType, const Json::Value& )> sendMessage,
                                           Domain::CharacterEquipment& equipment,
                                           Manager::ItemManager& itemManager );

    void onEnterWorld() override;
    void onTickWorld() override;
    void onExitWorld() override;

private:
    Domain::CharacterEquipment& _equipment;
    Manager::ItemManager& _itemManager;
};

} // namespace Engine

#endif // CHARACTEREQUIPMENTCONTROLLER_H
