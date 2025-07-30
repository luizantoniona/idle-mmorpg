#ifndef CHARACTERACTION_H
#define CHARACTERACTION_H

#include <string>

#include <json/json.h>

namespace Model {

class CharacterAction {
public:
    CharacterAction();

    Json::Value toJson();

    std::string idAction() const;
    void setIdAction( const std::string& idAction );

    int duration() const;
    void setDuration( int duration );

    int counter() const;
    void setCounter( int counter );

private:
    std::string _idAction;
    int _duration;
    int _counter;
};

} // namespace Model

#endif // CHARACTERACTION_H
