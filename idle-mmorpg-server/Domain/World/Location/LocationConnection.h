#ifndef LOCATIONCONNECTION_H
#define LOCATIONCONNECTION_H

#include <json/json.h>

#include <string>

#include <Domain/Requirement.h>

namespace Domain {

class LocationConnection {
public:
    LocationConnection();

    Json::Value toJson();

    std::string destination() const;
    void setDestination( const std::string& destination );

    std::string structure() const;
    void setStructure( const std::string& structure );

    std::string label() const;
    void setLabel( const std::string& label );

    int x() const;
    void setX( int x );

    int y() const;
    void setY( int y );

    std::vector<Requirement> requirements() const;
    void setRequirements( const std::vector<Requirement>& requirements );
    void addRequirement( const Requirement& requirement );

private:
    std::string _destination;
    std::string _structure;
    std::string _label;
    int _x;
    int _y;
    std::vector<Requirement> _requirements;
};

} // namespace Domain

#endif // LOCATIONCONNECTION_H
