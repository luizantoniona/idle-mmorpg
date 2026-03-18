#ifndef CHARACTERSTAGE_H
#define CHARACTERSTAGE_H

#include <json/json.h>

#include "CharacterStageObjective.h"

namespace Domain {

class CharacterStage {
public:
    CharacterStage();

    Json::Value toJson() const;

    int stageLevel() const;
    void setStageLevel( int stageLevel );

    bool completed() const;
    void setCompleted( bool completed );

    std::vector<CharacterStageObjective>& objectives();
    void setObjectives( const std::vector<CharacterStageObjective>& objectives );
    void addObjective( const CharacterStageObjective& objective );

private:
    int _stageLevel;
    bool _completed;

    std::vector<CharacterStageObjective> _objectives;

};

} // namespace Domain

#endif // CHARACTERSTAGE_H
