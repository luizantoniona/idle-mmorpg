#ifndef CHARACTERQUEST_H
#define CHARACTERQUEST_H

#include <string>

#include <json/json.h>

#include <Domain/Quest/Quest.h>

namespace Domain {

class CharacterQuest {
public:
    CharacterQuest();

    Json::Value toJson();

    std::string id() const;
    void setId( const std::string& id );

    std::string type() const;
    void setType( const std::string& type );

    std::string objectiveId() const;
    void setObjectiveId( const std::string& objectiveId );

    int currentAmount() const;
    void setCurrentAmount( int currentAmount );

    int objectiveAmount() const;
    void setObjectiveAmount( int objectiveAmount );

    bool finished() const;
    void setFinished( bool finished );

    const Quest* quest() const;
    void setQuest( const Quest* quest );

private:
    std::string _id;
    std::string _type;
    std::string _objectiveId;
    int _currentAmount;
    int _objectiveAmount;
    bool _finished;
    const Quest* _quest;
};

} // namespace Domain

#endif // CHARACTERQUEST_H
