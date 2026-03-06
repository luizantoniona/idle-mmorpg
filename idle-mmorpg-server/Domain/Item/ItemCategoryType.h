#ifndef ITEMCATEGORYTYPE_H
#define ITEMCATEGORYTYPE_H

namespace Domain {

enum class ItemCategoryType {
    // --- Consumable ---
    FOOD,

    // --- Diverse ---
    MATERIAL,
    ORE,

    // --- Equipment ---
    EQUIPMENT,

    // --- OffHand ---
    OFFHAND,

    // --- Tool ---
    TOOL,

    // --- Weapon ---
    WEAPON,

    UNKNOWN,
};

} // namespace Domain

#endif // ITEMCATEGORYTYPE_H
