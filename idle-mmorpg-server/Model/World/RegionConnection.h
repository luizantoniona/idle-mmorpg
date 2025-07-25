#ifndef REGIONCONNECTION_H
#define REGIONCONNECTION_H

#include <string>

namespace Model {

class RegionConnection {
public:
    RegionConnection();

    std::string origin() const;
    void setOrigin( const std::string& origin );

    std::string destination() const;
    void setDestination( const std::string& destination );

private:
    std::string _origin;
    std::string _destination;
};

} // namespace Model

#endif // REGIONCONNECTION_H
