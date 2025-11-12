#include "CharacterInventory.h"

#include <Engine/Manager/ItemManager.h>
#include <Shared/Commons/Singleton.h>

namespace Domain {

CharacterInventory::CharacterInventory() {
}

Json::Value CharacterInventory::toJson() {
    Json::Value root;
    for ( auto& item : items() ) {
        root[ "items" ].append( item.toJson() );
    }
    return root;
}

std::vector<CharacterInventoryItem>& CharacterInventory::items() {
    return _items;
}

void CharacterInventory::addItem( CharacterInventoryItem item ) {
    _items.push_back( item );
}

bool CharacterInventory::hasItem( const std::string& itemId, int amount ) {
    for ( const auto& item : _items ) {
        if ( item.id() == itemId ) {
            if ( item.amount() >= amount ) {
                return true;
            }
        }
    }

    return false;
}

bool CharacterInventory::removeItem( const std::string& itemId, int amount ) {
    for ( auto it = _items.begin(); it != _items.end(); ++it ) {
        if ( it->id() == itemId ) {

            if ( it->amount() < amount ) {
                return false;
            }

            it->setAmount( it->amount() - amount );

            if ( it->amount() <= 0 ) {
                _items.erase( it );
            }

            return true;
        }
    }
    return false;
}

bool CharacterInventory::addItem( const std::string& itemId, int amount ) {
    for ( auto& item : _items ) {
        if ( item.id() == itemId ) {
            item.setAmount( item.amount() + amount );
            return true;
        }
    }

    auto itemPtr = Commons::Singleton<Engine::ItemManager>::instance().itemById( itemId );
    if ( !itemPtr ) {
        return false;
    }

    Domain::CharacterInventoryItem newItem;
    newItem.setId( itemId );
    newItem.setAmount( amount );
    newItem.setItem( itemPtr );

    _items.push_back( newItem );

    return true;
}

CharacterInventoryItem* CharacterInventory::itemById( const std::string& itemId ) {
    for ( auto& item : _items ) {
        if ( item.id() == itemId ) {
            return &item;
        }
    }

    return nullptr;
}

} // namespace Domain
