#ifndef SKILLHELPER_H
#define SKILLHELPER_H

#include <string>

#include <Domain/Skill/SkillType.h>

namespace Domain {

class SkillHelper {
public:
    static SkillType stringToType( const std::string& type );
    static std::string typeToString( SkillType type );
};

} // namespace Domain

#endif // SKILLHELPER_H
