#ifndef COMBATHELPER_H
#define COMBATHELPER_H

#include <Domain/Item/Item.h>
#include <Domain/Skill/SkillType.h>

namespace Engine {

class CombatHelper {
public:
    static double attackSpeedByItem( const Domain::Item* item );

    static Domain::SkillType skillTypeByItem( const Domain::Item* item );
};

} // namespace Engine

#endif // COMBATHELPER_H
