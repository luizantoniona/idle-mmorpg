#include "StageObjective.h"

namespace Domain {

StageObjective::StageObjective() :
    _type( "" ),
    _target( "" ),
    _amount( 0 ) {
}

StageObjective::~StageObjective() = default;

Json::Value StageObjective::toJson() {
    Json::Value values;
    values[ "id" ] = _type;
    values[ "target" ] = target();
    values[ "amount" ] = amount();
    return values;
}

std::string StageObjective::type() const {
    return _type;
}

void StageObjective::setType( const std::string& type ) {
    _type = type;
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

} // namespace Domain
