import { DenizenQuest } from "./denizen-quest.model";
import { DenizenTrade } from "./denizen-trade.model";

export type Denizen = {
    id: string;
    name: string;
    icon: string;
    quests: DenizenQuest[];
    trade: DenizenTrade;
};
