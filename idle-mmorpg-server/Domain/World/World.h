#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <vector>

#include "Location/Location.h"

namespace Domain {

class World {
public:
    World();

    std::vector<std::unique_ptr<Location> >& locations();
    void setLocations( std::vector<std::unique_ptr<Location> > locations );
    void addLocation( std::unique_ptr<Location> location );

    Location* locationById( const std::string& locationId );
    bool hasLocationById( const std::string& locationId ) const;

private:
    std::vector<std::unique_ptr<Location> > _locations;
};

} // namespace Domain

#endif // WORLD_H
