#include "StageReward.h"

namespace Domain {

StageReward::StageReward() :
    _type( "" ),
    _id( "" ),
    _amount( 0 ) {
}

StageReward::~StageReward() = default;

std::string StageReward::type() const {
    return _type;
}

void StageReward::setType( const std::string& type ) {
    _type = type;
}

std::string StageReward::id() const {
    return _id;
}

void StageReward::setId( const std::string& id ) {
    _id = id;
}

int StageReward::amount() const {
    return _amount;
}

void StageReward::setAmount( int amount ) {
    _amount = amount;
}

} // namespace Domain
