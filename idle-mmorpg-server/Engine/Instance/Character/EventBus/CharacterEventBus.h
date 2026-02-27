#ifndef CHARACTEREVENTBUS_H
#define CHARACTEREVENTBUS_H

#include <functional>
#include <unordered_map>
#include <vector>

#include "CharacterEvent.h"

namespace Engine {

class CharacterEventBus {
public:
    using Listener = std::function<void( const CharacterEvent& )>;

    void subscribe( CharacterEventType type, Listener listener );
    void publish( const CharacterEvent& event );

private:
    std::unordered_map<CharacterEventType, std::vector<Listener>> _listeners;
};

} // namespace Engine

#endif // CHARACTEREVENTBUS_H
