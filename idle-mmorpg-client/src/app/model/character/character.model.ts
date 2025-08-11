import { CharacterAction } from "./character-action.model";
import { CharacterAttributes } from "./character-attributes.model";
import { CharacterCombatAction } from "./character-combat-action.model";
import { CharacterCombatAttributes } from "./character-combat-attributes.model";
import { CharacterCoordinates } from "./character-coordinates.model";
import { CharacterEquipment } from "./character-equipment.model";
import { CharacterInventory } from "./character-inventory.model";
import { CharacterProgression } from "./character-progression.model";
import { CharacterSkill } from "./character-skill.model";
import { CharacterVitals } from "./character-vitals.model";
import { CharacterWallet } from "./character-wallet.model";

export type Character = {
    idUser: number;
    idCharacter: number;
    name: string;
    action: CharacterAction;
    attributes: CharacterAttributes;
    combatAction: CharacterCombatAction;
    combatAttributes: CharacterCombatAttributes;
    coordinates: CharacterCoordinates;
    equipament: CharacterEquipment;
    inventory: CharacterInventory;
    progression: CharacterProgression;
    skills: CharacterSkill[];
    vitals: CharacterVitals;
    wallet: CharacterWallet;
};
