#ifndef ACTIONREQUIREMENT_H
#define ACTIONREQUIREMENT_H

namespace Domain {

class ActionRequirement {
public:
    ActionRequirement();

    int stage() const;
    void setStage( int stage );

    int level() const;
    void setLevel( int level );

private:
    int _stage;
    int _level;
};

} // namespace Domain

#endif // ACTIONREQUIREMENT_H
