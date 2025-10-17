#ifndef SKILLHELPER_H
#define SKILLHELPER_H

#include <string>

#include <Model/Skill/SkillType.h>

namespace Helper {

class SkillHelper {
public:
    static Model::SkillType stringToEnum( const std::string& type );
    static std::string enumToString( Model::SkillType type );
};

} // namespace Helper

#endif // SKILLHELPER_H
