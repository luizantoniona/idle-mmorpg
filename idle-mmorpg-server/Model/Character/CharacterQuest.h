#ifndef CHARACTERQUEST_H
#define CHARACTERQUEST_H

#include <string>

namespace Model {

class CharacterQuest {
public:
    CharacterQuest();

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

private:
    std::string _id;
    std::string _type;
    std::string _objectiveId;
    int _currentAmount;
    int _objectiveAmount;
    bool _finished;
};

} // namespace Model

#endif // CHARACTERQUEST_H
