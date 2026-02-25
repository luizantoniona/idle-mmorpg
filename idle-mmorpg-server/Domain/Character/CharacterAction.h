#ifndef CHARACTERACTION_H
#define CHARACTERACTION_H

#include <json/json.h>

#include <Domain/Action/Action.h>

namespace Domain {

class CharacterAction {
public:
    CharacterAction();

    Json::Value toJson() const;

    ActionType type() const;
    void setType( ActionType type );

    Action* action() const;
    void setAction( Action* action );

private:
    ActionType _type;
    Action* _action;
};

} // namespace Domain

#endif // CHARACTERACTION_H
