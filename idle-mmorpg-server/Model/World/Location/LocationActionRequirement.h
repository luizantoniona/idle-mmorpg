#ifndef LOCATIONACTIONREQUIREMENT_H
#define LOCATIONACTIONREQUIREMENT_H

#include <string>

namespace Model {

class LocationActionRequirement {
public:
    enum class RequirementType {
        Unknown,
        Skill,
        Item,
    };

    LocationActionRequirement();

    static RequirementType typeFromString( const std::string& type );
    static std::string typeToString( RequirementType type );

    RequirementType type() const;
    void setType( RequirementType type );

    std::string id() const;
    void setId( const std::string& id );

    int level() const;
    void setLevel( int level );

    std::string category() const;
    void setCategory( const std::string& category );

private:
    RequirementType _type;
    std::string _id;

    int _level;
    std::string _category;
};

} // namespace Model

#endif // LOCATIONACTIONREQUIREMENT_H
