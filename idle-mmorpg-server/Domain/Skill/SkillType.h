#ifndef SKILLTYPE_H
#define SKILLTYPE_H

namespace Domain {

enum class SkillType {
    // Vital
    ENDURANCE,
    MEDITATION,
    VITALITY,

    // Weapons and Combat
    AXE_MASTERY,
    DAGGER_MASTERY,
    SWORD_MASTERY,
    FIST_MASTERY,
    SHIELD_MASTERY,

    // Magic
    INVOCATION,
    RESTORATION,

    // Gathering
    FISHING,
    HERBALISM,
    MINING,
    WOODCUTTING,

    UNKNOWN
};

} // namespace Domain

#endif // SKILLTYPE_H
