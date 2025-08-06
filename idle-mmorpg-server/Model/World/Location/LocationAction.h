#ifndef LOCATIONACTION_H
#define LOCATIONACTION_H

#include <string>
#include <vector>

#include <json/json.h>

#include "LocationActionExperience.h"
#include "LocationActionRequirement.h"

namespace Model {

class LocationAction {
public:
    LocationAction();

    Json::Value toJson();

    std::string id() const;
    void setId( const std::string& id );

    std::string label() const;
    void setLabel( const std::string& label );

    std::string structure() const;
    void setStructure( const std::string& structure );

    int duration() const;
    void setDuration( int duration );

    std::vector<LocationActionRequirement> requirements() const;
    void setRequirements( const std::vector<LocationActionRequirement>& requirements );
    void addRequirement( const LocationActionRequirement& requirement );

    std::vector<LocationActionExperience> experience() const;
    void setExperience( const std::vector<LocationActionExperience>& experience );
    void addExperience( const LocationActionExperience& experience );

private:
    std::string _id;
    std::string _label;
    std::string _structure;
    int _duration;
    std::vector<LocationActionRequirement> _requirements;
    std::vector<LocationActionExperience> _experience;
};

} // namespace Model

#endif // LOCATIONACTION_H
