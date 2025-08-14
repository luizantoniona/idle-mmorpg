#include "LootSystem.h"

#include <algorithm>

#include <Commons/Singleton.h>
#include <Core/Manager/ItemManager.h>
#include <Core/System/NotificationSystem.h>

namespace Core::System {

void LootSystem::addItem( const std::string& sessionId, Model::Character* character, const std::string& itemId, int amount ) {
    if ( itemId == "copper_coin" || itemId == "silver_coin" || itemId == "gold_coin" ) {
        addCoin( sessionId, character, itemId, amount );
        return;
    }

    if ( amount > 0 ) {
        character->inventory().addItem( itemId, amount );
    }

    NotificationSystem::notifyCharacterInventory( sessionId, character );
}

void LootSystem::addCoin( const std::string& sessionId, Model::Character* character, const std::string& itemId, int amount ) {
    auto& characterWallet = character->wallet();

    if ( itemId == "copper_coin" ) {
        characterWallet.setCopper( characterWallet.copper() + amount );

    }else if ( itemId == "silver_coin" ) {
        characterWallet.setSilver( characterWallet.silver() + amount );

    }else if ( itemId == "gold_coin" ) {
        characterWallet.setGold( characterWallet.gold() + amount );
    }

    NotificationSystem::notifyCharacterWallet( sessionId, character );
}

} // namespace Core::System
