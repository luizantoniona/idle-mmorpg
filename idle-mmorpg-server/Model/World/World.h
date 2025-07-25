#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <vector>

#include "RegionConnection.h"
#include "Region.h"

namespace Model {

class World {
public:
    World();

    std::vector<std::unique_ptr<Region> >& regions();
    void setRegions( std::vector<std::unique_ptr<Region> > regions );
    void addRegion( std::unique_ptr<Region> region );

    std::vector<std::unique_ptr<RegionConnection> >& connections();
    void setConnections( std::vector<std::unique_ptr<RegionConnection> > connections );
    void addConnection( std::unique_ptr<RegionConnection> connection );

private:
    std::vector<std::unique_ptr<Region> > _regions;
    std::vector<std::unique_ptr<RegionConnection> > _connections;
};

} // namespace Model

#endif // WORLD_H
