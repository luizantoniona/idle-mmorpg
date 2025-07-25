#ifndef REGION_H
#define REGION_H

#include <memory>
#include <string>
#include <vector>

#include <Model/World/Location/LocationConnection.h>
#include <Model/World/Location/Location.h>

namespace Model {

class Region {
public:
    Region();

    std::string id() const;
    void setId( const std::string& id );

    std::string name() const;
    void setName( const std::string& name );

    std::string description() const;
    void setDescription( const std::string& description );

    std::vector<std::unique_ptr<Location> >& locations();
    void setLocations( std::vector<std::unique_ptr<Location> > locations );
    void addLocation( std::unique_ptr<Location> location );

    std::vector<std::unique_ptr<LocationConnection> >& connections();
    void setConnections( std::vector<std::unique_ptr<LocationConnection> >connections );
    void addConnection( std::unique_ptr<LocationConnection> connection );

    bool hasLocationWithCoordinates( int x, int y, int z ) const;
    Location* locationByCoordinates( int x, int y, int z );

private:
    std::string _id;
    std::string _name;
    std::string _description;
    std::vector<std::unique_ptr<Location> > _locations;
    std::vector<std::unique_ptr<LocationConnection> > _connections;
};

} // namespace Core::Model

#endif // REGION_H
