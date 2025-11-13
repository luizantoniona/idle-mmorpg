#include "DenizenManager.h"

#include "DenizenFactory.h"

namespace Engine {

DenizenManager::DenizenManager() :
    _denizens() {}

void DenizenManager::initialize( const std::string& denizensPath ) {
    _denizens = Engine::DenizenFactory::createDenizens( denizensPath );
}

Domain::Denizen* DenizenManager::denizenById( const std::string& idDenizen ) {
    auto it = _denizens.find( idDenizen );

    if ( it != _denizens.end() ) {
        return it->second.get();
    }

    return nullptr;
}

} // namespace Engine
