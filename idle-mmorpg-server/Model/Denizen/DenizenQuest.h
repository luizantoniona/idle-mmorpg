#ifndef DENIZENQUEST_H
#define DENIZENQUEST_H

#include <string>
#include <vector>

#include <json/json.h>

#include "DenizenQuestReward.h"

namespace Model {

class DenizenQuest {
public:
    DenizenQuest();

    Json::Value toJson() const;

    std::string id() const;
    void setId( const std::string& id );

    std::string title() const;
    void setTitle( const std::string& title );

    std::string description() const;
    void setDescription( const std::string& description );

    std::string type() const;
    void setType( const std::string& type );

    std::string objectiveId() const;
    void setObjectiveId( const std::string& objectiveId );

    int amount() const;
    void setAmount( int amount );

    std::vector<DenizenQuestReward> rewards() const;
    void setRewards( const std::vector<DenizenQuestReward>& rewards );
    void addReward( const DenizenQuestReward& reward );

private:
    std::string _id;
    std::string _title;
    std::string _description;
    std::string _type;
    std::string _objectiveId;
    int _amount;
    std::vector<DenizenQuestReward> _rewards;
};

} // namespace Model

#endif // DENIZENQUEST_H
