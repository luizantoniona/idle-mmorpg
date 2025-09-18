import { ItemBonus } from "./item-bonus.model";
import { ItemEffect } from "./item-effect.model";

export type Item = {
    id: string;
    amount: number;
    type: string;
    category: string;
    name: string;
    description: string;
    rarity: string;
    icon: string;
    price: number;
    bonuses: ItemBonus[];
    effects: ItemEffect[];
};
