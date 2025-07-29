import type { CharacterAttributes } from "./CharacterAttributes";
import type { CharacterWallet } from "./CharacterWallet";
import type { CharacterProgression } from "./CharacterProgression";
import type { CharacterVitals } from "./CharacterVitals";

export type Character = {
    idUser: number;
    idCharacter: number;
    name: string;
    attributes: CharacterAttributes;
    progression: CharacterProgression;
    vitals: CharacterVitals;
    wallet: CharacterWallet;
};
