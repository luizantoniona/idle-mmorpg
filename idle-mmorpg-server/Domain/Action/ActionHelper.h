#ifndef ACTIONHELPER_H
#define ACTIONHELPER_H

#include <string>

#include "ActionType.h"

namespace Domain {

class ActionHelper {
public:
    static ActionType stringToType( const std::string& type );
    static std::string typeToString( ActionType type );
};

} // namespace Domain

#endif // ACTIONHELPER_H
