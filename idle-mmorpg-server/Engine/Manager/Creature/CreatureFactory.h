#ifndef CREATUREFACTORY_H
#define CREATUREFACTORY_H

#include <memory>
#include <unordered_map>

#include <Domain/Creature/Creature.h>

namespace Manager {

class CreatureFactory {
public:
    static std::unordered_map<std::string, std::unique_ptr<Domain::Creature> > createCreatures( const std::string& creaturesPath );

private:
    static std::unique_ptr<Domain::Creature> createCreature( const std::string& creaturePath );
};

} // namespace Manager

#endif // CREATUREFACTORY_H
