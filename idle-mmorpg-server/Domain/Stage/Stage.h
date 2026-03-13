#ifndef STAGE_H
#define STAGE_H

#include "StageCreature.h"
#include "StageObjective.h"
#include "StageReward.h"

namespace Domain {

class Stage {
public:
    Stage();
    ~Stage();

    Json::Value toJson();

    int level() const;
    void setLevel( int level );

    std::vector<StageCreature> creatures() const;
    void setCreatures( const std::vector<StageCreature>& creatures );
    void addCreature( const StageCreature& creature );

    std::vector<StageObjective> objectives() const;
    void setObjectives( const std::vector<StageObjective>& objectives );
    void addObjective( const StageObjective& objective );

    std::vector<StageReward> rewards() const;
    void setRewards( const std::vector<StageReward>& rewards );
    void addReward( const StageReward& reward );

private:
    int _level;
    std::vector<StageCreature> _creatures;
    std::vector<StageObjective> _objectives;
    std::vector<StageReward> _rewards;
};

} // namespace Domain

#endif // STAGE_H
