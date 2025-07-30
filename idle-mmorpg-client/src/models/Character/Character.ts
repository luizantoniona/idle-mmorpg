import type { CharacterAction } from "./CharacterAction";
import type { CharacterAttributes } from "./CharacterAttributes";
import type { CharacterInventory } from "./CharacterInventory";
import type { CharacterProgression } from "./CharacterProgression";
import type { CharacterSkill } from "./CharacterSkill";
import type { CharacterVitals } from "./CharacterVitals";
import type { CharacterWallet } from "./CharacterWallet";

export type Character = {
    idUser: number;
    idCharacter: number;
    name: string;
    action: CharacterAction;
    attributes: CharacterAttributes;
    inventory: CharacterInventory;
    progression: CharacterProgression;
    skills: CharacterSkill[];
    vitals: CharacterVitals;
    wallet: CharacterWallet;
};
