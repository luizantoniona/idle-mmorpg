#ifndef ITEMSYSTEM_H
#define ITEMSYSTEM_H

#include <Domain/Character/Character.h>

namespace Core::System {

class ItemSystem {
public:
    static void characterUseItem( const std::string& sessionId, Domain::Character* character, const Json::Value& payload );
    static void characterEquipItem( const std::string& sessionId, Domain::Character* character, const Json::Value& payload );

    static void computeEquipmentModifiers( const std::string& sessionId, Domain::Character* character );
};

} // namespace Core::System

#endif // ITEMSYSTEM_H
