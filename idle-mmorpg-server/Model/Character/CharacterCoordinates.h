#ifndef CHARACTERCOORDINATES_H
#define CHARACTERCOORDINATES_H

#include <string>

#include <json/json.h>

namespace Model {

class CharacterCoordinates {
public:
    CharacterCoordinates();

    Json::Value toJson();

    int x() const;
    void setX( int x );

    int y() const;
    void setY( int y );

    int z() const;
    void setZ( int z );

    int xSpawn() const;
    void setXSpawn( int xSpawn );

    int ySpawn() const;
    void setYSpawn( int ySpawn );

    int zSpawn() const;
    void setZSpawn( int zSpawn );

    std::string currentStructure() const;
    void setCurrentStructure( const std::string& currentStructure );

private:
    int _x;
    int _y;
    int _z;
    int _xSpawn;
    int _ySpawn;
    int _zSpawn;
    std::string _currentStructure;
};

} // namespace Model

#endif // CHARACTERCOORDINATES_H
