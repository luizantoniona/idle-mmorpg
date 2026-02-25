#ifndef ACTIONOPTION_H
#define ACTIONOPTION_H

#include <string>

namespace Domain {

class ActionOption {
public:
    ActionOption();

    int stage() const;
    void setStage( int stage );

    const std::string& itemId() const;
    void setItemId( const std::string& id );

private:
    int _stage;
    std::string _itemId;
};

} // namespace Domain

#endif // ACTIONOPTION_H
