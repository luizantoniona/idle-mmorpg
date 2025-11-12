#ifndef DENIZEN_H
#define DENIZEN_H

#include <string>

#include <json/json.h>

#include "DenizenDialogue.h"
#include "DenizenQuest.h"
#include "DenizenTrade.h"

namespace Domain {

class Denizen {
public:
    Denizen();

    Json::Value toJson();

    std::string id() const;
    void setId( const std::string& id );

    std::string name() const;
    void setName( const std::string& name );

    std::string structure() const;
    void setStructure( const std::string& structure );

    std::string description() const;
    void setDescription( const std::string& description );

    std::string icon() const;
    void setIcon( const std::string& icon );

    std::vector<DenizenDialogue> dialogues() const;
    void setDialogues( const std::vector<DenizenDialogue>& dialogues );

    std::vector<DenizenQuest> quests() const;
    void setQuests( const std::vector<DenizenQuest>& quests );
    void addQuest( const DenizenQuest& quest );
    bool hasQuestById( const std::string& questId );

    DenizenTrade trade() const;
    void setTrade( const DenizenTrade& trade );

private:
    std::string _id;
    std::string _name;
    std::string _structure;
    std::string _description;
    std::string _icon;

    std::vector<DenizenDialogue> _dialogues;
    std::vector<DenizenQuest> _quests;
    DenizenTrade _trade;
};

} // namespace Domain

#endif // DENIZEN_H
