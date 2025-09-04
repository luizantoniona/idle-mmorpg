#ifndef CHARACTERATTRIBUTES_H
#define CHARACTERATTRIBUTES_H

#include <json/json.h>

namespace Model {

class CharacterAttributes {
public:
    CharacterAttributes();

    Json::Value toJson() const;

    double strength() const;
    void setStrength( double strength );

    double dexterity() const;
    void setDexterity( double dexterity );

    double constitution() const;
    void setConstitution( double constitution );

    double intelligence() const;
    void setIntelligence( double intelligence );

    double wisdom() const;
    void setWisdom( double wisdom );

private:
    double _strength;
    double _dexterity;
    double _constitution;
    double _intelligence;
    double _wisdom;
};

} // namespace Model

#endif // CHARACTERATTRIBUTES_H
