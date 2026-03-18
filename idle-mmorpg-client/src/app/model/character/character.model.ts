import { CharacterActions } from "./character-action.model";
import { CharacterCombat } from "./character-combat.model";
import { CharacterEffect } from "./character-effect.model";
import { CharacterEquipment } from "./character-equipment.model";
import { CharacterInventory } from "./character-inventory.model";
import { CharacterProgression } from "./character-progression.model";
import { CharacterSkill } from "./character-skill.model";
import { CharacterStage } from "./character-stage.model";
import { CharacterVitals } from "./character-vitals.model";
import { CharacterWallet } from "./character-wallet.model";

import { Spell } from "../spell/spell.model"

export type Character = {
    idCharacter: number;
    idUser: number;
    name: string;

    actions: CharacterActions;
    combat: CharacterCombat;
    effects: CharacterEffect[];
    equipment: CharacterEquipment;
    inventory: CharacterInventory;
    progression: CharacterProgression;
    skills: CharacterSkill[];
    spells: Spell[];
    stage: CharacterStage;
    vitals: CharacterVitals;
    wallet: CharacterWallet;
};
