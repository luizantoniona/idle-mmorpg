#include "QuestRequirement.h"

namespace Model {

QuestRequirement::QuestRequirement() :
    _type( "" ),
    _id( "" ),
    _amount( 0 ) {}

std::string QuestRequirement::type() const {
    return _type;
}

void QuestRequirement::setType( const std::string& type ) {
    _type = type;
}

std::string QuestRequirement::id() const {
    return _id;
}

void QuestRequirement::setId( const std::string& id ) {
    _id = id;
}

int QuestRequirement::amount() const {
    return _amount;
}

void QuestRequirement::setAmount( int amount ) {
    _amount = amount;
}

} // namespace Model
