#include "ItemManager.h"

#include "ItemFactory.h"

namespace Engine {

ItemManager::ItemManager() :
    _items() {
}

void ItemManager::initialize( const std::string& itemPath ) {
    _items = Engine::ItemFactory::createItems( itemPath );
}

const Domain::Item* ItemManager::itemById( const std::string& idItem ) const {
    auto it = _items.find( idItem );

    if ( it != _items.end() ) {
        return it->second.get();
    }

    return nullptr;
}

} // namespace Engine
