#ifndef WORLDFACTORY_H
#define WORLDFACTORY_H

#include <memory>

#include <Domain/World/World.h>

namespace Engine {

class WorldFactory {
public:
    static std::unique_ptr<Domain::World> createWorld( const std::string& mapPath );
};

} // namespace Engine

#endif // WORLDFACTORY_H
