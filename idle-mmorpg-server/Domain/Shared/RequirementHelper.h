#ifndef REQUIREMENTHELPER_H
#define REQUIREMENTHELPER_H

#include <string>

#include <Domain/Shared/RequirementType.h>

namespace Helper {

class RequirementHelper {
public:
    static Domain::RequirementType stringToEnum( const std::string& type );
};

} // namespace Helper

#endif // REQUIREMENTHELPER_H
