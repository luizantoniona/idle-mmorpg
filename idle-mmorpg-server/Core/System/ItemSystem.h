#ifndef ITEMSYSTEM_H
#define ITEMSYSTEM_H

#include <Model/Character/Character.h>

namespace Core::System {

class ItemSystem {
public:
    static void characterUseItem( const std::string& sessionId, Model::Character* character, const Json::Value& payload );
    static void characterEquipItem( const std::string& sessionId, Model::Character* character, const Json::Value& payload );

    static void computeEquipmentModifiers( const std::string& sessionId, Model::Character* character );
};

} // namespace Core::System

#endif // ITEMSYSTEM_H
