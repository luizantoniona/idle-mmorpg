#ifndef LOCATIONSTRUCTURE_H
#define LOCATIONSTRUCTURE_H

#include <string>

#include <json/json.h>

namespace Domain {

class LocationStructure {
public:
    LocationStructure();

    Json::Value toJson() const;

    std::string id() const;
    void setId( const std::string& id );

    std::string label() const;
    void setLabel( const std::string& label );

    std::string description() const;
    void setDescription( const std::string& description );

    int x() const;
    void setX( int x );

    int y() const;
    void setY( int y );

private:
    std::string _id;
    std::string _label;
    std::string _description;
    int _x;
    int _y;
};

} // namespace Domain

#endif // LOCATIONSTRUCTURE_H
