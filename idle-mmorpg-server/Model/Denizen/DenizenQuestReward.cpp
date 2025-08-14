#include "DenizenQuestReward.h"

namespace Model {

DenizenQuestReward::DenizenQuestReward() {
}

std::string DenizenQuestReward::type() const {
    return _type;
}

void DenizenQuestReward::setType( const std::string& type ) {
    _type = type;
}

std::string DenizenQuestReward::id() const {
    return _id;
}

void DenizenQuestReward::setId( const std::string& id ) {
    _id = id;
}

int DenizenQuestReward::getAmount() const {
    return amount;
}

void DenizenQuestReward::setAmount( int amount ) {
    this->amount = amount;
}

} // namespace Model
