import { Item } from "../item/item.model";

export type DenizenTrade = {
    sell: Item[];
    buy: Item[];
};
