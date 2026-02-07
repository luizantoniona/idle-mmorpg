#ifndef STAGE_H
#define STAGE_H

#include "StageCreature.h"
#include "StageObjective.h"

namespace Domain {

class Stage {
public:
    Stage();
    ~Stage();

    std::string id() const;
    void setId( const std::string& id );

    std::string name() const;
    void setName( const std::string& name );

    std::vector<StageCreature> creatures() const;
    void setCreatures( const std::vector<StageCreature>& creatures );
    void addCreature( const StageCreature& creature );

    std::vector<StageObjective> objectives() const;
    void setObjectives( const std::vector<StageObjective>& objectives );
    void addObjective( const StageObjective& objective );

private:
    std::string _id;
    std::string _name;
    std::vector<StageCreature> _creatures;
    std::vector<StageObjective> _objectives;
};

} // namespace Domain

#endif // STAGE_H
