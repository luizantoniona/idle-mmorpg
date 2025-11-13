#ifndef CHARACTERACTION_H
#define CHARACTERACTION_H

#include <string>

#include <json/json.h>

namespace Domain {

class CharacterAction {
public:
    CharacterAction();

    Json::Value toJson();

    std::string id() const;
    void setId( const std::string& id );

    int duration() const;
    void setDuration( int duration );

    int counter() const;
    void setCounter( int counter );

    void clear();

private:
    std::string _id;
    int _duration;
    int _counter;
};

} // namespace Domain

#endif // CHARACTERACTION_H
