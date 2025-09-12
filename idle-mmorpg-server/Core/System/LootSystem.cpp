#include "LootSystem.h"

#include <Commons/Singleton.h>
#include <Core/Manager/ItemManager.h>
#include <Core/System/NotificationSystem.h>
#include <Core/System/QuestSystem.h>

namespace Core::System {

void LootSystem::addItem( const std::string& sessionId, Model::Character* character, const std::string& itemId, int amount ) {
    if ( itemId == "coin_copper" || itemId == "coin_silver" || itemId == "coin_gold" ) {
        addCoin( sessionId, character, itemId, amount );
        return;
    }

    if ( amount > 0 ) {
        character->inventory().addItem( itemId, amount );
        QuestSystem::updateItemQuest( sessionId, character );
    }

    NotificationSystem::notifyCharacterInventory( sessionId, character );
}

void LootSystem::addCoin( const std::string& sessionId, Model::Character* character, const std::string& itemId, int amount ) {
    auto& characterWallet = character->wallet();

    if ( itemId == "coin_copper" ) {
        characterWallet.setCopper( characterWallet.copper() + amount );

    }else if ( itemId == "coin_silver" ) {
        characterWallet.setSilver( characterWallet.silver() + amount );

    }else if ( itemId == "coin_gold" ) {
        characterWallet.setGold( characterWallet.gold() + amount );
    }

    NotificationSystem::notifyCharacterWallet( sessionId, character );
}

} // namespace Core::System
