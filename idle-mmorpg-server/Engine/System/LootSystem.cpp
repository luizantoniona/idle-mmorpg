#include "LootSystem.h"

#include <Engine/Manager/Item/ItemManager.h>
#include <Engine/System/NotificationSystem.h>
#include <Engine/System/QuestSystem.h>
#include <Shared/Commons/Singleton.h>

namespace Engine {

void LootSystem::addItem( const std::string& sessionId, Domain::Character* character, const std::string& itemId, int amount ) {
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

void LootSystem::addCoin( const std::string& sessionId, Domain::Character* character, const std::string& itemId, int amount ) {
    auto& characterWallet = character->wallet();

    if ( itemId == "coin_copper" ) {
        characterWallet.setCopper( characterWallet.copper() + amount );

    } else if ( itemId == "coin_silver" ) {
        characterWallet.setSilver( characterWallet.silver() + amount );

    } else if ( itemId == "coin_gold" ) {
        characterWallet.setGold( characterWallet.gold() + amount );
    }

    NotificationSystem::notifyCharacterWallet( sessionId, character );
}

} // namespace Engine
