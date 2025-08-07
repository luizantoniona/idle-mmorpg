#ifndef CREATURELOOT_H
#define CREATURELOOT_H

#include <string>

namespace Model {

class CreatureLoot {
public:
    CreatureLoot();

    std::string id() const;
    void setId( const std::string& id );

    double chance() const;
    void setChance( double chance );

    int amount() const;
    void setAmount( int amount );

private:
    std::string _id;
    double _chance;
    int _amount;
};

} // namespace Model

#endif // CREATURELOOT_H
