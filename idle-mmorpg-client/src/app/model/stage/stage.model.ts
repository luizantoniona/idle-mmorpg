import { StageObjectives } from "./stage-objective.model";

export type Stage = {
    id: string;
    level: number;
    objectives: StageObjectives[];
};
