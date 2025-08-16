#ifndef EQUIPMENTSYSTEM_H
#define EQUIPMENTSYSTEM_H

#include <Model/Character/Character.h>

namespace Core::System {

class EquipmentSystem {
public:
    static void computeEquipmentModifiers( const std::string& sessionId, Model::Character* character );
    static void characterEquipItem( const std::string& sessionId, Model::Character* character, const Json::Value& payload );
};

} // namespace Core::System

#endif // EQUIPMENTSYSTEM_H
