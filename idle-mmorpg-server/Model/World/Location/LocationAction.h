#ifndef LOCATIONACTION_H
#define LOCATIONACTION_H

#include <string>
#include <vector>

#include "LocationActionRequirement.h"

namespace Model {

class LocationAction {
public:
    LocationAction();

    std::string id() const;
    void setId( const std::string& id );

    std::string label() const;
    void setLabel( const std::string& label );

    std::vector<LocationActionRequirement> requirements() const;
    void setRequirements( const std::vector<LocationActionRequirement>& requirements );
    void addRequirement( const LocationActionRequirement& requirement );

private:
    std::string _id;
    std::string _label;
    std::vector<LocationActionRequirement> _requirements;
};

} // namespace Model

#endif // LOCATIONACTION_H
