#ifndef LOCATION_H
#define LOCATION_H

#include <string>

#include <json/json.h>

#include "LocationAction.h"

namespace Model {

class Location {
public:
    Location();

    Json::Value toJson();

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
    void addAction( const LocationAction action );

private:
    std::string _id;
    std::string _name;
    std::string _description;
    int _x;
    int _y;
    int _z;
    std::vector<LocationAction> _actions;
};

} // namespace Core::Model

#endif // LOCATION_H
