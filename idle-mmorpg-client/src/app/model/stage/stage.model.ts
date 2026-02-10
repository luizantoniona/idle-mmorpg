import { StageObjectives } from "./stage-objective.model";

export type Stage = {
    id: string;
    name: string;
    objectives: StageObjectives[];
};
