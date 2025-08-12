#include "LootSystem.h"

#include <Commons/Singleton.h>
#include <Core/Manager/ItemManager.h>
#include <Core/System/NotificationSystem.h>

namespace Core::System {

void LootSystem::addItem( const std::string& sessionId, Model::Character* character, const std::string& itemId, int amount ) {
    auto& characterInventory = character->inventory();
    auto& items = characterInventory.items();

    auto it = std::find_if( items.begin(), items.end(), [ & ]( auto& item ) {
        return item.id() == itemId;
    } );

    if ( it != items.end() ) {
        it->setAmount( it->amount() + amount );

    } else {

        auto itemPtr = Commons::Singleton<Core::Manager::ItemManager>::instance().itemById( itemId );

        if ( !itemPtr ) {
            return;
        }

        Model::CharacterInventoryItem newItem;
        newItem.setId( itemId );
        newItem.setAmount( amount );
        newItem.setItem( itemPtr );
        characterInventory.addItem( newItem );
    }

    NotificationSystem::notifyCharacterInventory( sessionId, character );
}

} // namespace Core::System
