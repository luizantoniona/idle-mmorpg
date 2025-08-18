#ifndef LOCATIONCONNECTIONREQUIREMENT_H
#define LOCATIONCONNECTIONREQUIREMENT_H

#include <string>

namespace Model {

class LocationConnectionRequirement {
public:
    LocationConnectionRequirement();

    std::string type() const;
    void setType( const std::string& type );

    std::string id() const;
    void setId( const std::string& id );

    int amount() const;
    void setAmount( int amount );

private:
    std::string _type;
    std::string _id;
    int _amount;
};

} // namespace Model

#endif // LOCATIONCONNECTIONREQUIREMENT_H
