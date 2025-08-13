#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <vector>

#include "Region.h"

namespace Model {

class World {
public:
    World();

    std::vector<std::unique_ptr<Region> >& regions();
    void setRegions( std::vector<std::unique_ptr<Region> > regions );
    void addRegion( std::unique_ptr<Region> region );

private:
    std::vector<std::unique_ptr<Region> > _regions;
};

} // namespace Model

#endif // WORLD_H
