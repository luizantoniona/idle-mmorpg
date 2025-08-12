import { ItemModifier } from "./item.modifier.model";

export type Item = {
    id: string;
    amount: number;
    type: string;
    category: string;
    name: string;
    description: string;
    rarity: string;
    icon: string;
    value: number;
    modifiers: ItemModifier[];
};
