#ifndef ACTIONOPTION_H
#define ACTIONOPTION_H

#include <string>

namespace Domain {

class ActionOption {
public:
    ActionOption();

    int stage() const;
    void setStage( int stage );

    int duration() const;
    void setDuration( int duration );

    const std::string& itemId() const;
    void setItemId( const std::string& id );

private:
    int _stage;
    int _duration;
    std::string _itemId;
};

} // namespace Domain

#endif // ACTIONOPTION_H
