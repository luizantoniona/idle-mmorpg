export type CharacterStageObjective = {
    type: string;
    target: number;
    stageAmount: number;
    currentAmount: number;
};

export type CharacterStage = {
    id: number;
    completed: boolean;
    objectives: CharacterStageObjective[];
}; 