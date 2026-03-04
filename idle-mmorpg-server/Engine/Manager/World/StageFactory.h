#ifndef STAGEFACTORY_H
#define STAGEFACTORY_H

#include <Domain/Stage/Stage.h>

namespace Manager {

class StageFactory {
public:
    static std::unique_ptr<Domain::Stage> createStage( const std::string& stageFile );
};

} // namespace Manager

#endif // STAGEFACTORY_H
