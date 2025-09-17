#ifndef REQUIREMENTHELPER_H
#define REQUIREMENTHELPER_H

#include <string>

#include <Model/RequirementType.h>

namespace Helper {

class RequirementHelper {
public:
    static Model::RequirementType stringToEnum( const std::string& type );
};

} // namespace Helper

#endif // REQUIREMENTHELPER_H
