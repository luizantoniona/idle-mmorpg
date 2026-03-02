import { CreatureAction } from "./creature-action.model";
import { CreatureVitals } from "./creature-vitals.model";

export type Creature = {
    name: string;
    id: number;
    icon: string;
    actions: CreatureAction;
    vitals: CreatureVitals;
};
