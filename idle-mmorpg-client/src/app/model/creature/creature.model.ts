import { CreatureCombatAction } from "./creature-combat-action.model";
import { CreatureVitals } from "./creature-vitals.model";

export type Creature = {
    name: string;
    id: number;
    combatAction: CreatureCombatAction;
    vitals: CreatureVitals;
};
