#ifndef SPELLEFFECT_H
#define SPELLEFFECT_H

#include <string>

namespace Model {

class SpellEffect {
public:
    SpellEffect();

    std::string type() const;
    void setType( const std::string& type );

    double value() const;
    void setValue( double value );

private:
    std::string _type;
    double _value;
};

} // namespace Model

#endif // SPELLEFFECT_H
