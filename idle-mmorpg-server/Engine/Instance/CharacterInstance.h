#ifndef CHARACTERINSTANCE_H
#define CHARACTERINSTANCE_H

#include <Domain/Character/Character.h>

namespace Engine {

class CharacterInstance {
public:
    explicit CharacterInstance( std::unique_ptr<Domain::Character> );

    std::string sessionId() const;
    void setSessionId( const std::string& sessionId );

    Domain::Character& character();

    void onEnterWorld();
    void onLeaveWorld();

    void tick();

private:
    std::string _sessionId;
    std::unique_ptr<Domain::Character> _character;
};

} // namespace Engine

#endif // CHARACTERINSTANCE_H
