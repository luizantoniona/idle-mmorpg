#ifndef DENIZENQUESTREWARD_H
#define DENIZENQUESTREWARD_H

#include <string>

namespace Model {

class DenizenQuestReward {
public:
    DenizenQuestReward();

    std::string type() const;
    void setType( const std::string& type );

    std::string id() const;
    void setId( const std::string& id );

    int getAmount() const;
    void setAmount( int amount );

private:
    std::string _type;
    std::string _id;
    int amount;
};

} // namespace Model

#endif // DENIZENQUESTREWARD_H
