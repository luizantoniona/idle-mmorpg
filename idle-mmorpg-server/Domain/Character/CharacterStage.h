#ifndef CHARACTERSTAGE_H
#define CHARACTERSTAGE_H

#include <json/json.h>

namespace Domain {

class CharacterStage {
public:
    CharacterStage();

    Json::Value toJson() const;

    int stageLevel() const;
    void setStageLevel( int stageLevel );

    bool completed() const;
    void setCompleted( bool completed );

private:
    int _stageLevel;
    bool _completed;
};

} // namespace Domain

#endif // CHARACTERSTAGE_H
