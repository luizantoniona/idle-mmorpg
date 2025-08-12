#ifndef LOOTSYSTEM_H
#define LOOTSYSTEM_H

#include <string>

#include <Model/Character/Character.h>

namespace Core::System {

class LootSystem {
public:
    static void addItem( const std::string& sessionId, Model::Character* character, const std::string& itemId, int amount );
    static void addCoin( const std::string& sessionId, Model::Character* character, const std::string& itemId, int amount );
};

} // namespace Core::System

#endif // LOOTSYSTEM_H
