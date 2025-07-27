#ifndef WORLDFACTORY_H
#define WORLDFACTORY_H

#include <memory>

#include <Model/World/World.h>

namespace Core::Factory {

class WorldFactory {
public:
    static std::unique_ptr<Model::World> createWorld( const std::string& mapPath );
};

} // namespace Core::Factory

#endif // WORLDFACTORY_H
