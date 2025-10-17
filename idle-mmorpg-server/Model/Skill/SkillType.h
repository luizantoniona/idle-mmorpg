#ifndef SKILLTYPE_H
#define SKILLTYPE_H

namespace Model {

enum class SkillType {
    // Weapons and Combat
    AXE_MASTERY,
    DAGGER_MASTERY,
    SWORD_MASTERY,
    FIST_MASTERY,
    SHIELD_MASTERY,

    // Magic
    INVOCATION,
    RESTORATION,

    // Vital
    ENDURANCE,
    MEDITATION,
    VITALITY,

    // Gathering
    FISHING,
    HERBALISM,
    MINING,
    WOODCUTTING,

    UNKNOWN
};

} // namespace Model

#endif // SKILLTYPE_H
