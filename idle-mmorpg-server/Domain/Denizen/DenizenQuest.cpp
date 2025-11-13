#include "DenizenQuest.h"

namespace Domain {

DenizenQuest::DenizenQuest() {
}

Json::Value DenizenQuest::toJson() const {
    Json::Value root;
    root[ "id" ] = id();

    if ( _quest ) {
        root[ "title" ] = _quest->title();
        root[ "description" ] = _quest->description();
    }

    return root;
}

std::string DenizenQuest::id() const {
    return _id;
}

void DenizenQuest::setId( const std::string& id ) {
    _id = id;
}

const Quest* DenizenQuest::quest() const {
    return _quest;
}

void DenizenQuest::setQuest( const Quest* quest ) {
    _quest = quest;
}

} // namespace Domain
