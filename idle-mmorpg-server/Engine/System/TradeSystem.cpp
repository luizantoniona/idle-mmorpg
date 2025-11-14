#include "TradeSystem.h"

#include <Domain/World/Location/LocationHelper.h>

#include "NotificationSystem.h"
#include "QuestSystem.h"

namespace Engine {

void TradeSystem::characterTradeDenizen( const std::string& sessionId, Domain::Character* character, const Domain::Location* location, const Json::Value& payload ) {
    const std::string denizenId = payload[ "denizenId" ].asString();

    bool found = false;
    Domain::Denizen* denizenToTrade;
    for ( auto& denizen : location->denizens() ) {
        if ( denizenId == denizen->id() && Helper::LocationHelper::canCharacterInteractDenizen( character, *denizen ) ) {
            denizenToTrade = denizen;
            found = true;
            break;
        }
    }

    if ( !found ) {
        return;
    }

    Domain::CharacterWallet& wallet = character->wallet();
    Domain::CharacterInventory& inventory = character->inventory();

    int totalCoins = wallet.copper() + ( wallet.silver() * 1000 ) + ( wallet.gold() * 1000000 );

    if ( payload.isMember( "sell" ) && payload[ "sell" ].isArray() ) {

        for ( const auto& entry : payload[ "sell" ] ) {
            std::string itemId = entry[ "itemId" ].asString();
            int quantity = entry[ "quantity" ].asInt();

            if ( quantity <= 0 ) {
                continue;
            }

            const Domain::Item* itemToSell = nullptr;
            for ( const auto& item : denizenToTrade->trade().buyItems() ) {
                if ( item.id() == itemId ) {
                    itemToSell = item.item();
                    break;
                }
            }

            if ( !itemToSell ) {
                continue;
            }

            if ( !inventory.hasItem( itemId, quantity ) ) {
                continue;
            }

            int gain = itemToSell->price() * quantity;
            inventory.removeItem( itemId, quantity );
            totalCoins += gain;
        }
    }

    if ( payload.isMember( "buy" ) && payload[ "buy" ].isArray() ) {

        for ( const auto& entry : payload[ "buy" ] ) {
            std::string itemId = entry[ "itemId" ].asString();
            int quantity = entry[ "quantity" ].asInt();

            if ( quantity <= 0 ) {
                continue;
            }

            const Domain::Item* itemToBuy = nullptr;
            for ( const auto& item : denizenToTrade->trade().sellItems() ) {
                if ( item.id() == itemId ) {
                    itemToBuy = item.item();
                    break;
                }
            }

            if ( !itemToBuy ) {
                continue;
            }

            int cost = itemToBuy->price() * quantity;

            if ( totalCoins < cost ) {
                continue;
            }

            inventory.addItem( itemId, quantity );
            totalCoins -= cost;
        }
    }

    wallet.setGold( totalCoins / 1000000 );
    totalCoins %= 1000000;

    wallet.setSilver( totalCoins / 1000 );
    totalCoins %= 1000;

    wallet.setCopper( totalCoins );

    Engine::QuestSystem::updateItemQuest( sessionId, character );

    NotificationSystem::notifyCharacterInventory( sessionId, character );
    NotificationSystem::notifyCharacterWallet( sessionId, character );
    NotificationSystem::notifyLocation( sessionId, character );
}

} // namespace Engine
