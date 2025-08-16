import { Item } from "../item/item.model";

export type CharacterEquipment = {
    helmet: Item;
    armor: Item;
    leg: Item;
    boot: Item;
    glove: Item;

    leftHand: Item;
    rightHand: Item;

    amulet: Item;
    ring: Item;

    pickaxe: Item;
    woodaxe: Item;
    fishrod: Item;
    shovel: Item;
    sickle: Item;
};
