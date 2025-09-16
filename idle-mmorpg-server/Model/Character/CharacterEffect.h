#ifndef CHARACTEREFFECT_H
#define CHARACTEREFFECT_H

#include <json/json.h>

namespace Model {

class CharacterEffect {
public:
    CharacterEffect();

    Json::Value toJson();

    std::string id() const;
    void setId( const std::string& id );

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
    std::string _id;
    std::string _type;
    std::string _category;
    double _value;
    int _duration;
    int _counter;
};

} // namespace Model

#endif // CHARACTEREFFECT_H
