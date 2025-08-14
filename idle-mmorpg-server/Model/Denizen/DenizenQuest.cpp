#include "DenizenQuest.h"

namespace Model {

DenizenQuest::DenizenQuest() {
}

Json::Value DenizenQuest::toJson() const {
    Json::Value root;
    root[ "id" ] = id();
    root[ "title" ] = title();
    root[ "description" ] = description();
    return root;
}

std::string DenizenQuest::id() const {
    return _id;
}

void DenizenQuest::setId( const std::string& id ) {
    _id = id;
}

std::string DenizenQuest::title() const {
    return _title;
}

void DenizenQuest::setTitle( const std::string& title ) {
    _title = title;
}

std::string DenizenQuest::description() const {
    return _description;
}

void DenizenQuest::setDescription( const std::string& description ) {
    _description = description;
}

std::string DenizenQuest::type() const {
    return _type;
}

void DenizenQuest::setType( const std::string& type ) {
    _type = type;
}

std::string DenizenQuest::objectiveId() const {
    return _objectiveId;
}

void DenizenQuest::setObjectiveId( const std::string& objectiveId ) {
    _objectiveId = objectiveId;
}

int DenizenQuest::amount() const {
    return _amount;
}

void DenizenQuest::setAmount( int amount ) {
    _amount = amount;
}

std::vector<DenizenQuestReward> DenizenQuest::rewards() const {
    return _rewards;
}

void DenizenQuest::setRewards( const std::vector<DenizenQuestReward>& rewards ) {
    _rewards = rewards;
}

void DenizenQuest::addReward( const DenizenQuestReward& reward ) {
    _rewards.push_back( reward );
}

} // namespace Model
