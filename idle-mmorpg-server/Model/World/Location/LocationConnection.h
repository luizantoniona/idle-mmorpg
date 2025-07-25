#ifndef LOCATIONCONNECTION_H
#define LOCATIONCONNECTION_H

#include <string>

namespace Model {

class LocationConnection {
public:
    LocationConnection();

    std::string origin() const;
    void setOrigin( const std::string& origin );

    std::string destination() const;
    void setDestination( const std::string& destination );

    std::string direction() const;
    void setDirection( const std::string& direction );

private:
    std::string _origin;
    std::string _destination;
    std::string _direction;
};

} // namespace Model

#endif // LOCATIONCONNECTION_H
