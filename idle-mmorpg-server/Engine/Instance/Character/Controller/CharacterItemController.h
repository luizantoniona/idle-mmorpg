#ifndef CHARACTERITEMCONTROLLER_H
#define CHARACTERITEMCONTROLLER_H

#include <Domain/Character/Character.h>
#include <Engine/Manager/Item/ItemManager.h>

#include "CharacterController.h"

namespace Engine {

class CharacterItemController : public CharacterController {
public:
    explicit CharacterItemController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                      Domain::Character& character,
                                      Manager::ItemManager& itemManager );

    void onEnterWorld() override;
    void onLeaveWorld() override;

    void onTick() override;

    void handleMessage( MessageReceiverType type, const Json::Value& payload ) override;

private:
    void resolveInventory();
    void resolveItem( Domain::CharacterInventoryItem& item );

    void resolveEquipment();
    void resolveItem( Domain::CharacterEquipmentItem& item );

    Domain::CharacterEquipmentItem* resolveSlot( const std::string& slot );

    void handleEquip( const Json::Value& payload );
    void handleUseItem( const Json::Value& payload );

    // --- EventBus methods ---
    void onItemGained( const CharacterEvent& event );

private:
    Domain::CharacterEquipment& _characterEquipment;
    Domain::CharacterInventory& _characterInventory;
    Domain::CharacterWallet& _characterWallet;
    Manager::ItemManager& _itemManager;
};

} // namespace Engine

#endif // CHARACTERITEMCONTROLLER_H
