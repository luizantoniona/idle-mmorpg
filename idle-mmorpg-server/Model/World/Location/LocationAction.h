#ifndef LOCATIONACTION_H
#define LOCATIONACTION_H

#include <string>
#include <vector>

#include <json/json.h>

#include <Model/Requirement.h>

#include "LocationActionExperience.h"
#include "LocationActionLoot.h"

namespace Model {

class LocationAction {
public:
    LocationAction();

    Json::Value toJson();

    std::string id() const;
    void setId( const std::string& id );

    std::string type() const;
    void setType( const std::string& type );

    std::string label() const;
    void setLabel( const std::string& label );

    std::string structure() const;
    void setStructure( const std::string& structure );

    int duration() const;
    void setDuration( int duration );

    std::vector<Requirement> requirements() const;
    void setRequirements( const std::vector<Requirement>& requirements );
    void addRequirement( const Requirement& requirement );

    std::vector<LocationActionExperience> experience() const;
    void setExperience( const std::vector<LocationActionExperience>& experience );
    void addExperience( const LocationActionExperience& experience );

    std::vector<LocationActionLoot> loot() const;
    void setLoot( const std::vector<LocationActionLoot>& loot );
    void addLoot( const LocationActionLoot& loot );

private:
    std::string _id;
    std::string _type;
    std::string _label;
    std::string _structure;
    int _duration;
    std::vector<Requirement> _requirements;
    std::vector<LocationActionExperience> _experience;
    std::vector<LocationActionLoot> _loot;
};

} // namespace Model

#endif // LOCATIONACTION_H
