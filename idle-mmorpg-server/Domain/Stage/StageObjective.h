#ifndef STAGEOBJECTIVE_H
#define STAGEOBJECTIVE_H

#include <string>
#include <vector>

#include "StageObjectiveReward.h"

namespace Domain {

class StageObjective {
public:
    StageObjective();
    ~StageObjective();

    std::string id() const;
    void setId( const std::string& id );

    std::string target() const;
    void setTarget( const std::string& target );

    int amount() const;
    void setAmount( int amount );

    std::vector<StageObjectiveReward> rewards() const;
    void setRewards( const std::vector<StageObjectiveReward>& rewards );
    void addReward( const StageObjectiveReward& reward );

private:
    std::string _id;
    std::string _target;
    int _amount;
    std::vector<StageObjectiveReward> _rewards;
};

} // namespace Domain

#endif // STAGEOBJECTIVE_H
