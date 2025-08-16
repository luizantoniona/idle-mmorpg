#ifndef QUESTREQUIREMENT_H
#define QUESTREQUIREMENT_H

#include <string>

namespace Model {

class QuestRequirement {
public:
    QuestRequirement();

    std::string type() const;
    void setType( const std::string& type );

    std::string requirementId() const;
    void setRequirementId( const std::string& requirementId );

    int amount() const;
    void setAmount( int amount );

private:
    std::string _type;
    std::string _requirementId;
    int _amount;
};

} // namespace Model

#endif // QUESTREQUIREMENT_H
