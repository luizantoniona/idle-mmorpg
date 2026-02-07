#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <vector>

#include <Domain/Stage/Stage.h>

namespace Domain {

class World {
public:
    World();

    std::vector<std::unique_ptr<Stage>>& stages();
    const std::vector<std::unique_ptr<Stage>>& stages() const;

    void setStages( std::vector<std::unique_ptr<Stage>> stages );
    void addStage( std::unique_ptr<Stage> stage );

    Stage* stageById( const std::string& stageId );
    bool hasStageById( const std::string& stageId ) const;

private:
    std::vector<std::unique_ptr<Stage>> _stages;
};

} // namespace Domain

#endif // WORLD_H
