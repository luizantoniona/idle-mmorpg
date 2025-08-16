#include "EquipmentSystem.h"

#include <iostream>

#include "LootSystem.h"
#include "NotificationSystem.h"
#include "QuestSystem.h"

namespace Core::System {

void EquipmentSystem::computeEquipmentModifiers( const std::string& sessionId, Model::Character* character ) {
    // VERIFICAR TODOS OS EQUIPAMENTOS E AUMENTAR OS MODIFIERS DE ATTRIBUTES E COMBATATTRIBUTES

    NotificationSystem::notifyCharacterAttributes( sessionId, character );
    NotificationSystem::notifyCharacterCombatAttributes( sessionId, character );
}

void EquipmentSystem::characterEquipItem( const std::string& sessionId, Model::Character* character, const Json::Value& payload ) {
    const std::string itemId = payload[ "itemId" ].asString();
    const std::string slot = payload[ "slot" ].asString();

    auto& characterInventory = character->inventory();
    auto& characterEquipments = character->equipment();

    std::unordered_map<std::string, Model::CharacterEquipmentItem&> slotMap = {
        { "helmet", characterEquipments.helmet() },
        { "armor", characterEquipments.armor() },
        { "leg", characterEquipments.leg() },
        { "boot", characterEquipments.boot() },
        { "glove", characterEquipments.glove() },
        { "leftHand", characterEquipments.leftHand() },
        { "rightHand", characterEquipments.rightHand() },
        { "amulet", characterEquipments.amulet() },
        { "ring", characterEquipments.ring() },
        { "pickaxe", characterEquipments.pickaxe() },
        { "woodaxe", characterEquipments.woodaxe() },
        { "fishrod", characterEquipments.fishrod() },
        { "shovel", characterEquipments.shovel() },
        { "sickle", characterEquipments.sickle() },
    };

    auto it = slotMap.find( slot );
    if ( it == slotMap.end() ) {
        std::cerr << "EquipmentSystem::characterEquipItem Unknown slot: " << slot << std::endl;
        return;
    }

    Model::CharacterEquipmentItem& targetSlot = it->second;

    if ( !targetSlot.id().empty() ) {
        character->inventory().addItem( targetSlot.id(), 1 );
        targetSlot.setId( "" );
        targetSlot.setItem( nullptr );
    }

    if ( !itemId.empty() ) {

        if ( !characterInventory.hasItem( itemId, 1 ) ) {
            std::cerr << "EquipmentSystem::characterEquipItem Item not found in inventory: " << itemId << std::endl;
            return;
        }

        const Model::CharacterInventoryItem* itemToEquip = characterInventory.itemById( itemId );

        bool canEquip = ( slot == itemToEquip->item()->category() ) ||
                        ( ( slot == "leftHand" || slot == "rightHand" ) && itemToEquip->item()->type() == "weapon" );

        if ( !canEquip ) {
            std::cerr << "EquipmentSystem::characterEquipItem Item cannot be equipped in this slot: " << slot << std::endl;
            return;
        }

        targetSlot.setItem( itemToEquip->item() );
        targetSlot.setId( itemToEquip->id() );

        characterInventory.removeItem( itemId, 1 );
    }

    computeEquipmentModifiers( sessionId, character );
    QuestSystem::updateItemQuest( sessionId, character );
    NotificationSystem::notifyCharacterInventory( sessionId, character );
    NotificationSystem::notifyCharacterEquipment( sessionId, character );
}

} // namespace Core::System
