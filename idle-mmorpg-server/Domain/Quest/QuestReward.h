#ifndef QUESTREWARD_H
#define QUESTREWARD_H

#include <string>

namespace Domain {

class QuestReward {
public:
    QuestReward();

    std::string type() const;
    void setType( const std::string& type );

    std::string id() const;
    void setId( const std::string& id );

    int amount() const;
    void setAmount( int amount );

private:
    std::string _type;
    std::string _id;
    int _amount;
};

} // namespace Domain

#endif // QUESTREWARD_H
