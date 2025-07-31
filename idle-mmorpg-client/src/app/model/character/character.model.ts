import type { CharacterAction } from "./character-action.model";
import type { CharacterAttributes } from "./character-attributes";
import type { CharacterEquipament } from "./character-equipament";
import type { CharacterInventory } from "./character-inventory";
import type { CharacterProgression } from "./character-progression";
import type { CharacterSkill } from "./character-skill";
import type { CharacterVitals } from "./character-vitals";
import type { CharacterWallet } from "./character-wallet";

export type Character = {
    idUser: number;
    idCharacter: number;
    name: string;
    action: CharacterAction;
    attributes: CharacterAttributes;
    equipament: CharacterEquipament;
    inventory: CharacterInventory;
    progression: CharacterProgression;
    skills: CharacterSkill[];
    vitals: CharacterVitals;
    wallet: CharacterWallet;
};
