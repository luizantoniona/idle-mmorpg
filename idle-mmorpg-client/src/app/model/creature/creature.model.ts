import { CreatureCombat } from "./creature-combat.model";
import { CreatureVitals } from "./creature-vitals.model";

export type Creature = {
    name: string;
    id: number;
    icon: string;
    combat: CreatureCombat;
    vitals: CreatureVitals;
};
