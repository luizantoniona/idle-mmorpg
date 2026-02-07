#include "StageObjectiveReward.h"

namespace Domain {

StageObjectiveReward::StageObjectiveReward() :
    _type( "" ),
    _id( "" ),
    _amount( 0 ) {
}

StageObjectiveReward::~StageObjectiveReward() = default;

std::string StageObjectiveReward::type() const {
    return _type;
}

void StageObjectiveReward::setType( const std::string& type ) {
    _type = type;
}

std::string StageObjectiveReward::id() const {
    return _id;
}

void StageObjectiveReward::setId( const std::string& id ) {
    _id = id;
}

int StageObjectiveReward::amount() const {
    return _amount;
}

void StageObjectiveReward::setAmount( int amount ) {
    _amount = amount;
}

} // namespace Domain
