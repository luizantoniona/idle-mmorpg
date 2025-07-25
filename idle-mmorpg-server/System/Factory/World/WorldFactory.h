#ifndef WORLDFACTORY_H
#define WORLDFACTORY_H

#include <memory>

#include <Model/World/World.h>

namespace System::Factory {

class WorldFactory {
public:
    static std::unique_ptr<Model::World> createWorld( const std::string& mapPath );
};

} // namespace System::Factory

#endif // WORLDFACTORY_H
