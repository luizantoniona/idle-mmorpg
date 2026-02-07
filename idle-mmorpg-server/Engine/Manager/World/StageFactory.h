#ifndef STAGEFACTORY_H
#define STAGEFACTORY_H

#include <Domain/Stage/Stage.h>

namespace Engine {

class StageFactory {
public:
    static std::unique_ptr<Domain::Stage> createStage( const std::string& stageId, const std::string& stageFile );
};

} // namespace Engine

#endif // STAGEFACTORY_H
