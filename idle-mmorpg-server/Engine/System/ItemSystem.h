#ifndef ITEMSYSTEM_H
#define ITEMSYSTEM_H

#include <Domain/Character/Character.h>

namespace Engine {

class ItemSystem {
public:
    static void characterUseItem( const std::string& sessionId, Domain::Character* character, const Json::Value& payload );
    static void characterEquipItem( const std::string& sessionId, Domain::Character* character, const Json::Value& payload );

    static void computeEquipmentModifiers( const std::string& sessionId, Domain::Character* character );
};

} // namespace Engine

#endif // ITEMSYSTEM_H
