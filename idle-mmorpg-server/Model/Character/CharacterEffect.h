#ifndef CHARACTEREFFECT_H
#define CHARACTEREFFECT_H

#include <json/json.h>

namespace Model {

class CharacterEffect {
public:
    CharacterEffect();

    Json::Value toJson();

    std::string source() const;
    void setSource( const std::string& source );

    std::string sourceName() const;
    void setSourceName( const std::string& sourceName );

    std::string type() const;
    void setType( const std::string& type );

    std::string category() const;
    void setCategory( const std::string& category );

    double value() const;
    void setValue( double value );

    int duration() const;
    void setDuration( int duration );

    int counter() const;
    void setCounter( int counter );

private:
    std::string _source;
    std::string _sourceName;
    std::string _type;
    std::string _category;
    double _value;
    int _duration;
    int _counter;
};

} // namespace Model

#endif // CHARACTEREFFECT_H
