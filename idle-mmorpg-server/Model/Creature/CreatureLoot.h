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

    int minAmount() const;
    void setMinAmount( int minAmount );

    int maxAmount() const;
    void setMaxAmount( int maxAmount );

private:
    std::string _id;
    double _chance;
    int _minAmount;
    int _maxAmount;
};

} // namespace Model

#endif // CREATURELOOT_H
