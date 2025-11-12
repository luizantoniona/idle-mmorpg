#include "Quest.h"

namespace Domain {

Quest::Quest() {
}

Json::Value Quest::toJson() const {
    Json::Value root;
    root[ "id" ] = id();
    root[ "denizenId" ] = denizenId();
    root[ "title" ] = title();
    root[ "description" ] = description();
    return root;
}

std::string Quest::id() const {
    return _id;
}

void Quest::setId( const std::string& id ) {
    _id = id;
}

std::string Quest::denizenId() const {
    return _denizenId;
}

void Quest::setDenizenId( const std::string& denizenId ) {
    _denizenId = denizenId;
}

std::string Quest::title() const {
    return _title;
}

void Quest::setTitle( const std::string& title ) {
    _title = title;
}

std::string Quest::description() const {
    return _description;
}

void Quest::setDescription( const std::string& description ) {
    _description = description;
}

std::string Quest::type() const {
    return _type;
}

void Quest::setType( const std::string& type ) {
    _type = type;
}

std::string Quest::objectiveId() const {
    return _objectiveId;
}

void Quest::setObjectiveId( const std::string& objectiveId ) {
    _objectiveId = objectiveId;
}

int Quest::amount() const {
    return _amount;
}

void Quest::setAmount( int amount ) {
    _amount = amount;
}

std::vector<Requirement> Quest::requirements() const {
    return _requirements;
}

void Quest::setRequirements( const std::vector<Requirement>& requirements ) {
    _requirements = requirements;
}

void Quest::addRequirement( const Requirement& requirement ) {
    _requirements.push_back( requirement );
}

std::vector<QuestReward> Quest::rewards() const {
    return _rewards;
}

void Quest::setRewards( const std::vector<QuestReward>& rewards ) {
    _rewards = rewards;
}

void Quest::addReward( const QuestReward& reward ) {
    _rewards.push_back( reward );
}

} // namespace Domain
