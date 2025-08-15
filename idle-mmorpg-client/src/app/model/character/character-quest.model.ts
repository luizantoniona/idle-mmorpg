export type CharacterQuest = {
    id: string;
    type: string;
    currentAmount: number;
    objectiveAmount: number;
    finished: boolean;
    title: string;
    description: string;
};
