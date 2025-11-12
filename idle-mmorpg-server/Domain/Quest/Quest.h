#ifndef QUEST_H
#define QUEST_H

#include <string>
#include <vector>

#include <json/json.h>

#include <Domain/Shared/Requirement.h>

#include "QuestReward.h"

namespace Domain {

class Quest {
public:
    Quest();

    Json::Value toJson() const;

    std::string id() const;
    void setId( const std::string& id );

    std::string denizenId() const;
    void setDenizenId( const std::string& denizenId );

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

    std::vector<Requirement> requirements() const;
    void setRequirements( const std::vector<Requirement>& requirements );
    void addRequirement( const Requirement& requirement );

    std::vector<QuestReward> rewards() const;
    void setRewards( const std::vector<QuestReward>& rewards );
    void addReward( const QuestReward& reward );

private:
    std::string _id;
    std::string _denizenId;
    std::string _title;
    std::string _description;
    std::string _type;
    std::string _objectiveId;
    int _amount;
    std::vector<Requirement> _requirements;
    std::vector<QuestReward> _rewards;
};

} // namespace Domain

#endif // QUEST_H
