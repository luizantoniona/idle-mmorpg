#ifndef SKILLHELPER_H
#define SKILLHELPER_H

#include <string>

#include <Domain/Skill/SkillType.h>

namespace Helper {

class SkillHelper {
public:
    static Domain::SkillType stringToEnum( const std::string& type );
    static std::string enumToString( Domain::SkillType type );
};

} // namespace Helper

#endif // SKILLHELPER_H
