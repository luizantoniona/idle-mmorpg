#ifndef CREATUREFACTORY_H
#define CREATUREFACTORY_H

#include <memory>
#include <unordered_map>

#include <Model/Creature/Creature.h>

namespace Core::Factory {

class CreatureFactory {
public:
    static std::unordered_map<std::string, std::unique_ptr<Model::Creature> > createCreatures( const std::string& creaturesPath );

private:
    static std::unique_ptr<Model::Creature> createCreature( const std::string& creaturePath );
};

} // namespace Core::Factory

#endif // CREATUREFACTORY_H
