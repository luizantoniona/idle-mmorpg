#ifndef CHARACTERACTION_H
#define CHARACTERACTION_H

#include <string>

namespace Model {

class CharacterAction {
public:
    CharacterAction();

    std::string idAction() const;
    void setIdAction( const std::string& idAction );

    int duration() const;
    void setDuration( int duration );

private:
    std::string _idAction;
    int _duration;
};

} // namespace Model

#endif // CHARACTERACTION_H
