import type { CharacterAction } from "./character-action.model";
import type { CharacterAttributes } from "./character-attributes.model";
import type { CharacterEquipament } from "./character-equipament.model";
import type { CharacterInventory } from "./character-inventory.model";
import type { CharacterProgression } from "./character-progression.model";
import type { CharacterSkill } from "./character-skill.model";
import type { CharacterVitals } from "./character-vitals.model";
import type { CharacterWallet } from "./character-wallet.model";

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
