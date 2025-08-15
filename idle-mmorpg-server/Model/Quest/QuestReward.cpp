#include "QuestReward.h"

namespace Model {

QuestReward::QuestReward() {
}

std::string QuestReward::type() const {
    return _type;
}

void QuestReward::setType( const std::string& type ) {
    _type = type;
}

std::string QuestReward::id() const {
    return _id;
}

void QuestReward::setId( const std::string& id ) {
    _id = id;
}

int QuestReward::amount() const {
    return _amount;
}

void QuestReward::setAmount( int amount ) {
    _amount = amount;
}

} // namespace Model
