#include "Requirement.h"

namespace Model {

Requirement::Requirement() :
    _type( RequirementType::UNKNOWN ),
    _id( "" ),
    _amount( 0 ) {
}

RequirementType Requirement::type() const {
    return _type;
}

void Requirement::setType( RequirementType type ) {
    _type = type;
}

std::string Requirement::id() const {
    return _id;
}

void Requirement::setId( const std::string& id ) {
    _id = id;
}

int Requirement::amount() const {
    return _amount;
}

void Requirement::setAmount( int amount ) {
    _amount = amount;
}

} // namespace Model
