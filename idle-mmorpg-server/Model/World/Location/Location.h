#ifndef LOCATION_H
#define LOCATION_H

#include <string>

#include <json/json.h>

#include "LocationAction.h"
#include "LocationCreature.h"
#include "LocationStructure.h"

namespace Model {

class Location {
public:
    Location();

    Json::Value toJson() const;

    std::string id() const;
    void setId( const std::string& id );

    std::string name() const;
    void setName( const std::string& name );

    std::string description() const;
    void setDescription( const std::string& description );

    int x() const;
    void setX( int x );

    int y() const;
    void setY( int y );

    int z() const;
    void setZ( int z );

    const std::vector<LocationAction>& actions() const;
    void setActions( const std::vector<LocationAction>& actions );
    void addAction( const LocationAction& action );

    std::vector<LocationCreature> creatures() const;
    void setCreatures( const std::vector<LocationCreature>& creatures );
    void addCreature( const LocationCreature& creature );

    const std::vector<LocationStructure>& structures() const;
    void setStructures( const std::vector<LocationStructure>& structures );
    void addStructure( const LocationStructure& structure );

private:
    std::string _id;
    std::string _name;
    std::string _description;
    int _x;
    int _y;
    int _z;
    std::vector<LocationAction> _actions;
    std::vector<LocationCreature> _creatures;
    std::vector<LocationStructure> _structures;
};

} // namespace Core::Model

#endif // LOCATION_H
