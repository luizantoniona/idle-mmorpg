#ifndef CHARACTERCOORDINATES_H
#define CHARACTERCOORDINATES_H

#include <string>

#include <json/json.h>

#include <Domain/World/Location/Location.h>

namespace Domain {

class CharacterCoordinates {
public:
    CharacterCoordinates();

    Json::Value toJson();

    std::string locationId() const;
    void setLocationId( const std::string& locationId );

    std::string spawnLocationId() const;
    void setSpawnLocationId( const std::string& locationId );

    std::string structureId() const;
    void setStructureId( const std::string& structureId );

    std::string spawnStructureId() const;
    void setSpawnStructureId( const std::string& structureId );

    Location* location() const;
    void setLocation( Location* location );

private:
    std::string _locationId;
    std::string _spawnLocationId;
    std::string _structureId;
    std::string _spawnStructureId;
    Location* _location;
};

} // namespace Domain

#endif // CHARACTERCOORDINATES_H
