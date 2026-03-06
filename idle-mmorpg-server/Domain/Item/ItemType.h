#ifndef ITEMTYPE_H
#define ITEMTYPE_H

namespace Domain {

enum class ItemType {
    CONSUMABLE,
    DIVERSE,
    EQUIPMENT,
    OFFHAND,
    TOOL,
    WEAPON,

    UNKNOWN,
};

} // namespace Domain

#endif // ITEMTYPE_H
