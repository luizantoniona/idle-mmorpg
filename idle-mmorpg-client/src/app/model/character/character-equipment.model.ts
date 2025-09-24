import { Item } from "../item/item.model";

export type CharacterEquipment = {
    helmet: Item;
    armor: Item;
    leg: Item;
    boot: Item;

    weapon: Item;
    offhand: Item;

    amulet: Item;
    ring: Item;

    pickaxe: Item;
    woodaxe: Item;
    fishingrod: Item;
    sickle: Item;
};
