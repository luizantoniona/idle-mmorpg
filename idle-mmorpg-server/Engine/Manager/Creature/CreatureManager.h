#ifndef CREATUREMANAGER_H
#define CREATUREMANAGER_H

#include <memory>
#include <string>
#include <unordered_map>

#include <Domain/Creature/Creature.h>

namespace Engine {

class CreatureManager {
public:
    CreatureManager();

    void initialize( const std::string& creaturesPath );

    const Domain::Creature* creatureById( const std::string& idCreature ) const;

private:
    std::unordered_map<std::string, std::unique_ptr<Domain::Creature> > _creatures;
};

} // namespace Engine

#endif // CREATUREMANAGER_H
