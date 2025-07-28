import type { CharacterAttributes } from "./CharacterAttributes";
import type { CharacterWallet } from "./CharacterWallet";

export type Character = {
    idUser: number;
    idCharacter: number;
    name: string;
    attributes: CharacterAttributes;
    wallet: CharacterWallet;
};
