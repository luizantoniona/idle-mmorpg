import { Character } from "../character/character.model";
import { Creature } from "../creature/creature.model";

export type Combat = {
    characters: Character[];
    creatures: Creature[];
};
