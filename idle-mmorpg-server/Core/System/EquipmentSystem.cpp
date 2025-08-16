#include "EquipmentSystem.h"

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

    auto& inventory = character->inventory();

    if ( itemId == "" ) {

        // TODO DESEQUIPAR ITEM SE TER NO SLOT

    } else {
        // bool hasItem( const std::string& itemId, int amount );
    }

    computeEquipmentModifiers( sessionId, character );
    QuestSystem::updateItemQuest( sessionId, character );
    NotificationSystem::notifyCharacterInventory( sessionId, character );
    NotificationSystem::notifyCharacterEquipment( sessionId, character );
}

} // namespace Core::System
