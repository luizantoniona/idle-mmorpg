#ifndef CHARACTERSTAGEOBJECTIVE_H
#define CHARACTERSTAGEOBJECTIVE_H

#include <string>

namespace Domain {

class CharacterStageObjective {
public:
    CharacterStageObjective();

    const std::string& idObjective() const;
    void setIdObjective( const std::string& idObjective );

    int currentAmount() const;
    void setCurrentAmount( int currentAmount );

    bool completed() const;
    void setCompleted( bool completed );

private:
    std::string _idObjective;
    int _currentAmount = 0;
    bool _completed = false;
};

} // namespace Domain

#endif // CHARACTERSTAGEOBJECTIVE_H
