#ifndef CHARACTERACTIONS_H
#define CHARACTERACTIONS_H

#include <vector>

#include <json/json.h>

#include "CharacterAction.h"

namespace Domain {

class CharacterActions {
public:
    CharacterActions();

    Json::Value toJson() const;

    CharacterAction currentAction() const;
    void setCurrentAction( CharacterAction currentAction );

    std::vector<CharacterAction>& actions();
    void setActions( const std::vector<CharacterAction>& actions );
    void addAction( const CharacterAction& action );
    void clearActions();

    int duration() const;
    void setDuration( int duration );

    int counter() const;
    void setCounter( int counter );

private:
    CharacterAction _currentAction;
    std::vector<CharacterAction> _actions;

    int _duration;
    int _counter;
};

} // namespace Domain

#endif // CHARACTERACTIONS_H
