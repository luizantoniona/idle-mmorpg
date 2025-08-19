#include "SpellEffect.h"

namespace Model {

SpellEffect::SpellEffect() :
    _type( "" ),
    _value( 0.0 ) {
}

std::string SpellEffect::type() const {
    return _type;
}

void SpellEffect::setType( const std::string& type ) {
    _type = type;
}

double SpellEffect::value() const {
    return _value;
}

void SpellEffect::setValue( double value ) {
    _value = value;
}

} // namespace Model
