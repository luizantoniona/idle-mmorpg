#include "ItemManager.h"

#include <Core/Factory/Item/ItemFactory.h>

namespace Core::Manager {

ItemManager::ItemManager() :
    _items() {}

void ItemManager::initialize( const std::string& itemPath ) {
    _items = Core::Factory::ItemFactory::createItems( itemPath );
}

const Model::Item* ItemManager::itemById( const std::string& idItem ) const {
    auto it = _items.find( idItem );

    if ( it != _items.end() ) {
        return it->second.get();
    }

    return nullptr;
}

} // namespace Core::Manager
