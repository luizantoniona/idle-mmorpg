#include "Denizen.h"

namespace Model {

Denizen::Denizen() {}

Json::Value Denizen::toJson() {
    Json::Value root;
    root[ "id" ] = id();
    root[ "name" ] = name();
    root[ "icon" ] = icon();
    root[ "trade" ] = trade().toJson();

    Json::Value questsJson;
    for ( auto quest : quests() ) {
        questsJson.append( quest.toJson() );
    }
    root[ "quests" ] = questsJson;

    return root;
}

std::string Denizen::id() const {
    return _id;
}

void Denizen::setId( const std::string& id ) {
    _id = id;
}

std::string Denizen::name() const {
    return _name;
}

void Denizen::setName( const std::string& name ) {
    _name = name;
}

std::string Denizen::structure() const {
    return _structure;
}

void Denizen::setStructure( const std::string& structure ) {
    _structure = structure;
}

std::string Denizen::description() const {
    return _description;
}

void Denizen::setDescription( const std::string& description ) {
    _description = description;
}

std::string Denizen::icon() const {
    return _icon;
}

void Denizen::setIcon( const std::string& icon ) {
    _icon = icon;
}

std::vector<DenizenDialogue> Denizen::dialogues() const {
    return _dialogues;
}

void Denizen::setDialogues( const std::vector<DenizenDialogue>& dialogues ) {
    _dialogues = dialogues;
}

std::vector<DenizenQuest> Denizen::quests() const {
    return _quests;
}

void Denizen::setQuests( const std::vector<DenizenQuest>& quests ) {
    _quests = quests;
}

void Denizen::addQuest( const DenizenQuest& quest ) {
    _quests.push_back( quest );
}

DenizenTrade Denizen::trade() const {
    return _trade;
}

void Denizen::setTrade( const DenizenTrade& trade ) {
    _trade = trade;
}

} // namespace Model
