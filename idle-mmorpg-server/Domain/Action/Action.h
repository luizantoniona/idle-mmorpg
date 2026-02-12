#ifndef ACTION_H
#define ACTION_H

#include <string>

#include "ActionType.h"

namespace Domain {

class Action {
public:
    Action();

    std::string id() const;
    void setId( const std::string& id );

    ActionType type() const;
    void setType( ActionType type );

private:
    std::string _id;
    ActionType _type;
};

} // namespace Domain

#endif // ACTION_H
