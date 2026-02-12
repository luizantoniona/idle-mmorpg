#ifndef CHARACTERACTIONS_H
#define CHARACTERACTIONS_H

#include <string>

#include <json/json.h>

#include <Domain/Action/ActionType.h>

namespace Domain {

class CharacterActions {
public:
    CharacterActions();

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

#endif // CHARACTERACTIONS_H
