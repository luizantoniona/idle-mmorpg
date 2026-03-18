export type CharacterStageObjective = {
    type: string;
    target: number;
    stageAmount: number;
    currentAmount: number;
};

export type CharacterStage = {
    stageLevel: number;
    completed: boolean;
    objectives: CharacterStageObjective[];
}; 