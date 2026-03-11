#ifndef ITEMCATEGORY_H
#define ITEMCATEGORY_H

namespace Domain {

enum class ItemCategory {
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

#endif // ITEMCATEGORY_H
