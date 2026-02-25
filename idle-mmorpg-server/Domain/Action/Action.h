#ifndef ACTION_H
#define ACTION_H

#include <vector>

#include "ActionOption.h"
#include "ActionRequirement.h"
#include "ActionType.h"

namespace Domain {

class Action {
public:
    Action();

    ActionType type() const;
    void setType( ActionType type );

    std::string description() const;
    void setDescription( const std::string& description );

    const ActionRequirement& requirement() const;
    void setRequirement( const ActionRequirement& requirement );

    const std::vector<ActionOption>& options() const;
    void addOption( const ActionOption& option );

private:
    ActionType _type;
    std::string _description;

    ActionRequirement _requirement;
    std::vector<ActionOption> _options;
};

} // namespace Domain

#endif // ACTION_H
