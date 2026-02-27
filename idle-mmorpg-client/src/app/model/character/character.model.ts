import { CharacterActions } from "./character-action.model";
import { CharacterEffect } from "./character-effect.model";
import { CharacterEquipment } from "./character-equipment.model";
import { CharacterInventory } from "./character-inventory.model";
import { CharacterProgression } from "./character-progression.model";
import { CharacterSkill } from "./character-skill.model";
import { CharacterSpells } from "./character-spells.model";
import { CharacterVitals } from "./character-vitals.model";
import { CharacterWallet } from "./character-wallet.model";

export type Character = {
    idCharacter: number;
    idUser: number;
    name: string;

    // --- Persistent Data
    equipment: CharacterEquipment;
    inventory: CharacterInventory;
    progression: CharacterProgression;
    skills: CharacterSkill[];
    spells: CharacterSpells;
    vitals: CharacterVitals;
    wallet: CharacterWallet;

    // --- Runtime Data
    actions: CharacterActions;
    effects: CharacterEffect[];
};
