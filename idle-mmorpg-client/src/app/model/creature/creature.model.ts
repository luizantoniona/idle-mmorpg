import { CreatureCombatAction } from "./creature-combat-action.model";
import { CreatureVitals } from "./creature-vitals.model";

export type Creature = {
    name: string;
    id: number;
    icon: string;
    combatAction: CreatureCombatAction;
    vitals: CreatureVitals;
};
