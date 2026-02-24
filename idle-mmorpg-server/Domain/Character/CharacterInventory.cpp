#include "CharacterInventory.h"

namespace Domain {

CharacterInventory::CharacterInventory() {}

Json::Value CharacterInventory::toJson() {
    Json::Value values;
    for ( auto& item : items() ) {
        values.append( item.toJson() );
    }

    Json::Value inventory;
    inventory[ "inventory" ] = values;
    return inventory;
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

void CharacterInventory::addItem( const std::string& itemId, int amount ) {
    for ( auto& item : _items ) {
        if ( item.id() == itemId ) {
            item.setAmount( item.amount() + amount );
            return;
        }
    }

    CharacterInventoryItem newItem;
    newItem.setId( itemId );
    newItem.setAmount( amount );

    _items.push_back( newItem );
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
