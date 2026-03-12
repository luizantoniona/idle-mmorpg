#ifndef ITEMCATEGORYTYPE_H
#define ITEMCATEGORYTYPE_H

namespace Domain {

enum class ItemCategoryType {
    // --- Consumable ---
    FOOD,
    POTION,

    // --- Diverse ---
    MATERIAL,
    ORE,

    // --- Equipment ---
    HELMET,
    ARMOR,
    LEG,
    BOOT,
    AMULET,
    RING,

    // --- OffHand ---
    SHIELD,

    // --- Tools ---
    FISHINGROD,
    SICKLE,
    PICKAXE,
    WOODAXE,

    // --- Weapons ---
    AXE,
    DAGGER,
    SWORD,

    UNKNOWN,
};

} // namespace Domain

#endif // ITEMCATEGORYTYPE_H
