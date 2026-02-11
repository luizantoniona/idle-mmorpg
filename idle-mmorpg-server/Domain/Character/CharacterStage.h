#ifndef CHARACTERSTAGE_H
#define CHARACTERSTAGE_H

#include <string>

namespace Domain {

class CharacterStage {
public:
    CharacterStage();

    std::string idStage() const;
    void setIdStage( const std::string& idStage );

    bool completed() const;
    void setCompleted( bool completed );

private:
    std::string _idStage;
    bool _completed;
};

} // namespace Domain

#endif // CHARACTERSTAGE_H
