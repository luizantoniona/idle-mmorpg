import { CharacterQuest } from "./character-quest.model";

export type CharacterQuests = {
    proceeding: CharacterQuest[];
    finished: CharacterQuest[];
};