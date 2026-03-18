#ifndef CHARACTERSTAGEOBJECTIVE_H
#define CHARACTERSTAGEOBJECTIVE_H

#include <string>

#include <json/json.h>

namespace Domain {

class CharacterStageObjective {
public:
    CharacterStageObjective();
    ~CharacterStageObjective();

    Json::Value toJson() const;

    std::string type() const;
    void setType( const std::string& type );

    std::string target() const;
    void setTarget( const std::string& target );

    int stageAmount() const;
    void setStageAmount( int stageAmount );

    int currentAmount() const;
    void setCurrentAmount( int currentAmount );

private:
    std::string _type;
    std::string _target;
    int _stageAmount;
    int _currentAmount;
};

} // namespace Domain

#endif // CHARACTERSTAGEOBJECTIVE_H
