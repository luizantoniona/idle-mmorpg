import { ItemBonus } from "./item-bonus.model";
import { ItemCombat } from "./item-combat.model";
import { ItemEffect } from "./item-effect.model";

export type Item = {
    id: string;
    amount: number;
    type: string;
    category: string;
    name: string;
    description: string;
    icon: string;
    price: number;
    combat: ItemCombat;
    bonuses: ItemBonus[];
    effects: ItemEffect[];
};
