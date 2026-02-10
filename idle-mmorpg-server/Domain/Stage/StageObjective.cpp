#include "StageObjective.h"

namespace Domain {

StageObjective::StageObjective() :
    _id( "" ),
    _target( "" ),
    _amount( 0 ),
    _rewards( {} ) {
}

StageObjective::~StageObjective() = default;

Json::Value StageObjective::toJson() {
    Json::Value root;
    root[ "id" ] = id();
    root[ "target" ] = target();
    root[ "amount" ] = amount();

    return root;
}

std::string StageObjective::id() const {
    return _id;
}

void StageObjective::setId( const std::string& id ) {
    _id = id;
}

std::string StageObjective::target() const {
    return _target;
}

void StageObjective::setTarget( const std::string& target ) {
    _target = target;
}

int StageObjective::amount() const {
    return _amount;
}

void StageObjective::setAmount( int amount ) {
    _amount = amount;
}

std::vector<StageObjectiveReward> StageObjective::rewards() const {
    return _rewards;
}

void StageObjective::setRewards( const std::vector<StageObjectiveReward>& rewards ) {
    _rewards = rewards;
}

void StageObjective::addReward( const StageObjectiveReward& reward ) {
    _rewards.push_back( reward );
}

} // namespace Domain
