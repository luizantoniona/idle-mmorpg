#ifndef WORLDFACTORY_H
#define WORLDFACTORY_H

#include <memory>

#include <Domain/World/World.h>

namespace Manager {

class WorldFactory {
public:
    static std::unique_ptr<Domain::World> createWorld( const std::string& mapPath );
};

} // namespace Manager

#endif // WORLDFACTORY_H
