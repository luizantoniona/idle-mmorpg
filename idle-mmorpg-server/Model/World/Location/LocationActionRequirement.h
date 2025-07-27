#ifndef LOCATIONACTIONREQUIREMENT_H
#define LOCATIONACTIONREQUIREMENT_H

#include <string>

namespace Model {

class LocationActionRequirement {
public:
    LocationActionRequirement();

    std::string type() const;
    void setType( const std::string& type );

    std::string id() const;
    void setId( const std::string& id );

    int level() const;
    void setLevel( int level );

    std::string category() const;
    void setCategory( const std::string& category );

private:
    std::string _type;
    std::string _id;

    int _level;
    std::string _category;
};

} // namespace Model

#endif // LOCATIONACTIONREQUIREMENT_H
