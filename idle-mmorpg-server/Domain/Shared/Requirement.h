#ifndef REQUIREMENT_H
#define REQUIREMENT_H

#include <string>

#include "RequirementType.h"

namespace Domain {

class Requirement {
public:
    Requirement();

    RequirementType type() const;
    void setType( RequirementType type );

    std::string id() const;
    void setId( const std::string& id );

    int amount() const;
    void setAmount( int amount );

private:
    RequirementType _type;
    std::string _id;
    int _amount;
};

} // namespace Domain

#endif // REQUIREMENT_H
