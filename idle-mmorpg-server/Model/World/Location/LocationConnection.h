#ifndef LOCATIONCONNECTION_H
#define LOCATIONCONNECTION_H

#include <json/json.h>

#include <string>

namespace Model {

class LocationConnection {
public:
    LocationConnection();

    Json::Value toJson();

    std::string destination() const;
    void setDestination( const std::string& destination );

    std::string direction() const;
    void setDirection( const std::string& direction );

private:
    std::string _destination;
    std::string _direction;
};

} // namespace Model

#endif // LOCATIONCONNECTION_H
