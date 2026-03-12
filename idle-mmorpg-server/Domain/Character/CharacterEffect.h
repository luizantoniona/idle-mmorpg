#ifndef CHARACTEREFFECT_H
#define CHARACTEREFFECT_H

#include <json/json.h>

namespace Domain {

class CharacterEffect {
public:
    CharacterEffect();

    Json::Value toJson();

    std::string source() const;
    void setSource( const std::string& source );

    std::string sourceName() const;
    void setSourceName( const std::string& sourceName );

    double health() const;
    void setHealth( double health );

    double mana() const;
    void setMana( double mana );

    double stamina() const;
    void setStamina( double stamina );

    int duration() const;
    void setDuration( int duration );

    int counter() const;
    void setCounter( int counter );

private:
    std::string _source;
    std::string _sourceName;

    double _health;
    double _mana;
    double _stamina;

    int _duration;
    int _counter;
};

} // namespace Domain

#endif // CHARACTEREFFECT_H
