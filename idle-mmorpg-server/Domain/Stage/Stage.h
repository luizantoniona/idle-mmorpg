#ifndef STAGE_H
#define STAGE_H

#include "StageCreature.h"
#include "StageObjective.h"

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

private:
    int _level;
    std::vector<StageCreature> _creatures;
    std::vector<StageObjective> _objectives;
};

} // namespace Domain

#endif // STAGE_H
