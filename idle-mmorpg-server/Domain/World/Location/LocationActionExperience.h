#ifndef LOCATIONACTIONEXPERIENCE_H
#define LOCATIONACTIONEXPERIENCE_H

#include <string>

namespace Domain {

class LocationActionExperience {
public:
    LocationActionExperience();

    std::string idSkill() const;
    void setIdSkill( const std::string& idSkill );

    int amount() const;
    void setAmount( int amount );

private:
    std::string _idSkill;
    int _amount;
};

} // namespace Domain

#endif // LOCATIONACTIONEXPERIENCE_H
