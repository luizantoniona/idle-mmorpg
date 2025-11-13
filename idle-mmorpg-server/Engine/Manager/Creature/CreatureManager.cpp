#include "CreatureManager.h"

#include "CreatureFactory.h"

namespace Engine {

CreatureManager::CreatureManager() :
    _creatures() {}

void CreatureManager::initialize( const std::string& creaturesPath ) {
    _creatures = Engine::CreatureFactory::createCreatures( creaturesPath );
}

const Domain::Creature* CreatureManager::creatureById( const std::string& idCreature ) const {
    auto it = _creatures.find( idCreature );

    if ( it != _creatures.end() ) {
        return it->second.get();
    }

    return nullptr;
}

} // namespace Engine
