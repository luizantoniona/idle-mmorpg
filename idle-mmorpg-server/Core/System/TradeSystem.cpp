#include "TradeSystem.h"

#include <Commons/LocationHelper.h>

#include "NotificationSystem.h"

namespace Core::System {

void TradeSystem::characterTradeDenizen( const std::string& sessionId, Model::Character* character, const Model::Location* location, const Json::Value& payload ) {
    const std::string denizenId = payload["denizenId"].asString();

    bool found = false;
    Model::Denizen denizenToTrade;
    for ( auto& denizen : location->denizens() ) {
        if ( denizenId == denizen.id() && Commons::LocationHelper::canCharacterInteractDenizen( character, denizen ) ) {
            denizenToTrade = denizen;
            found = true;
            break;
        }
    }

    if ( !found ) {
        return;
    }

    Model::CharacterWallet& wallet = character->wallet();
    Model::CharacterInventory& inventory = character->inventory();

    int totalCoins = wallet.copper() + ( wallet.silver() * 1000 ) + ( wallet.gold() * 1000000 );

    if ( payload.isMember( "sell" ) && payload["sell"].isArray() ) {

        for ( const auto& entry : payload["sell"] ) {
            std::string itemId = entry["itemId"].asString();
            int quantity = entry["quantity"].asInt();

            if ( quantity <= 0 ) {
                continue;
            }

            const Model::Item* itemToSell = nullptr;
            for ( const auto& item : denizenToTrade.trade().buyItems() ) {
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

            int gain = itemToSell->value() * quantity;
            inventory.removeItem( itemId, quantity );
            totalCoins += gain;
        }
    }

    if ( payload.isMember( "buy" ) && payload["buy"].isArray() ) {

        for ( const auto& entry : payload["buy"] ) {
            std::string itemId = entry["itemId"].asString();
            int quantity = entry["quantity"].asInt();

            if ( quantity <= 0 ) {
                continue;
            }

            const Model::Item* itemToBuy = nullptr;
            for ( const auto& item : denizenToTrade.trade().sellItems() ) {
                if ( item.id() == itemId ) {
                    itemToBuy = item.item();
                    break;
                }
            }

            if ( !itemToBuy ) {
                continue;
            }

            int cost = itemToBuy->value() * quantity;

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

    NotificationSystem::notifyCharacterInventory( sessionId, character );
    NotificationSystem::notifyCharacterWallet( sessionId, character );
    NotificationSystem::notifyLocationDenizens( sessionId, character, location );
}

} // namespace Core::System
