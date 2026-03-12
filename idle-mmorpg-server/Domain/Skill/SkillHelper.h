#ifndef SKILLHELPER_H
#define SKILLHELPER_H

#include <string>

#include "SkillMilestoneType.h"
#include "SkillType.h"

namespace Domain {

class SkillHelper {
public:
    static SkillType stringToType( const std::string& type );
    static std::string typeToString( SkillType type );

    static SkillMilestoneType stringToMilestoneType( const std::string& type );
    static std::string milestoneTypeToString( SkillMilestoneType type );
};

} // namespace Domain

#endif // SKILLHELPER_H
