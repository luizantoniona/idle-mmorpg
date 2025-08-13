import { Item } from "../item/item.model";

export type CharacterEquipment = {
    head: Item;
    chest: Item;
    legs: Item;
    boots: Item;
    gloves: Item;

    leftHand: Item;
    rightHand: Item;

    amulet: Item;
    ring: Item;

    pickaxe: Item;
    woodaxe: Item;
    rod: Item;
    shovel: Item;
    sickle: Item;
};
