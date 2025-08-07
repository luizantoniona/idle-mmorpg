#ifndef CREATUREMANAGER_H
#define CREATUREMANAGER_H

#include <memory>
#include <string>
#include <unordered_map>

#include <Model/Creature/Creature.h>

namespace Core::Manager {

class CreatureManager {
public:
    CreatureManager();

    void initialize( const std::string& creaturesPath );

    const Model::Creature* creatureById( const std::string& idCreature ) const;

private:
    std::unordered_map<std::string, std::unique_ptr<Model::Creature> > _creatures;
};

} // namespace Core::Manager

#endif // CREATUREMANAGER_H
