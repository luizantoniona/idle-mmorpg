#ifndef CHARACTERCOORDINATES_H
#define CHARACTERCOORDINATES_H

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

private:
    int _x;
    int _y;
    int _z;
    int _xSpawn;
    int _ySpawn;
    int _zSpawn;
};

} // namespace Model

#endif // CHARACTERCOORDINATES_H
