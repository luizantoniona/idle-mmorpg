#ifndef CHARACTERSTAGE_H
#define CHARACTERSTAGE_H

#include <string>
#include <vector>

#include "CharacterStageObjective.h"

namespace Domain {

class CharacterStage {
public:
    CharacterStage();

    std::string idStage() const;
    void setIdStage( const std::string& idStage );

    bool completed() const;
    void setCompleted( bool completed );

    std::vector<CharacterStageObjective>& objectives();
    const std::vector<CharacterStageObjective>& objectives() const;

    CharacterStageObjective* findObjective( const std::string& objectiveId );

private:
    std::string _idStage;
    bool _completed = false;
    std::vector<CharacterStageObjective> _objectives;
};

} // namespace Domain

#endif // CHARACTERSTAGE_H
