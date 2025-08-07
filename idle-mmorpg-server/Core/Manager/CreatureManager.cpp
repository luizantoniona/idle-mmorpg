#include "CreatureManager.h"

#include <Core/Factory/Creature/CreatureFactory.h>

namespace Core::Manager {

CreatureManager::CreatureManager() :
    _creatures() {}

void CreatureManager::initialize( const std::string& creaturesPath ) {
    _creatures = Core::Factory::CreatureFactory::createCreatures( creaturesPath );
}

const Model::Creature* CreatureManager::creatureById( const std::string& idCreature ) const {
    auto it = _creatures.find( idCreature );

    if ( it != _creatures.end() ) {
        return it->second.get();
    }

    return nullptr;
}

} // namespace Core::Manager
